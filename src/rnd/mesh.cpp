#include "mesh.h"
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>

int Mesh::sRevision = 0;
bool Mesh::sWireframe = false;
const int MESH_VERSION = 1;

void Vertex::Load(Stream& strm) {
    float f;
    strm >> pos;
    strm >> norm;
    strm >> uv;
    strm >> col;
}

void Vertex::Save(Stream& strm) {
    strm << pos;
    strm << norm;
    strm << uv;
    strm << col;
}

Mesh::Mesh() : mVerts(), mFaces() {}

Mesh::~Mesh() { mVerts.clear(); mFaces.clear(); }

/*
0x4: version
0x4: vert count
(vertcount*sizeof(Vertex)): verts
0x4: face count
(facecount*sizeof(Face)): faces
*/

void Mesh::Load(Stream& strm) {
    strm >> sRevision;
    SDL_assert(sRevision <= MESH_VERSION);
    int vertct;
    strm >> vertct;
    mVerts.resize(vertct);
    for (Vertex& v : mVerts) v.Load(strm);
    int facect;
    strm >> facect;
    mFaces.resize(facect);
    for (Face& f : mFaces) f.Load(strm);
}

void Mesh::Save(Stream& strm) {
    strm << uint32_t(MESH_VERSION);
    strm << uint32_t(mVerts.size());
    for (Vertex v : mVerts) v.Save(strm);
    strm << uint32_t(mFaces.size());
    for (Face f : mFaces) f.Save(strm);
}

void Mesh::Draw() {
    // TODO init tex
    for (Face& f : mFaces) {
        if (sWireframe) {
            glEnd();
            glBegin(GL_LINE_LOOP);
        }
        glColor4fv((float*)&mVerts[f.idx0].col);
        glVertex3fv((float*)&mVerts[f.idx0].pos);
        glNormal3fv((float*)&mVerts[f.idx0].norm);
        glTexCoord2fv((float*)&mVerts[f.idx0].uv);

        glColor4fv((float*)&mVerts[f.idx1].col);
        glVertex3fv((float*)&mVerts[f.idx1].pos);
        glNormal3fv((float*)&mVerts[f.idx1].norm);
        glTexCoord2fv((float*)&mVerts[f.idx1].uv);

        glColor4fv((float*)&mVerts[f.idx2].col);
        glVertex3fv((float*)&mVerts[f.idx2].pos);
        glNormal3fv((float*)&mVerts[f.idx2].norm);
        glTexCoord2fv((float*)&mVerts[f.idx2].uv);
        if (sWireframe) {
            glEnd();
            glBegin(GL_TRIANGLES);
        }
    }
}

void Mesh::ImportOBJ(std::ifstream& strm) {
    char linebuf[256] = {0};
    uint32_t vtx_pos_ct, vtx_norm_ct, vtx_uv_ct;
    while (!strm.fail()) {
        strm.getline(linebuf, 256);
        if (linebuf[0] == 'v') {
            Vertex vtx;
            bool new_pos_vtx, new_norm_vtx, new_uv_vtx;
            switch (linebuf[1]) {
                case ' ':
                    vtx_pos_ct++;
                    new_pos_vtx = true;
                    SDL_assert(sscanf(linebuf, "v %f %f %f", &vtx.pos.x, &vtx.pos.y, &vtx.pos.z) == 3);
                    vtx.pos.z = -vtx.pos.z;
                    break;
                case 'n':
                    vtx_norm_ct++;
                    new_norm_vtx = true;
                    SDL_assert(sscanf(linebuf, "vn %f %f %f", &vtx.norm.x, &vtx.norm.y, &vtx.norm.z) == 3);
                    break;
                case 't':
                    vtx_uv_ct++;
                    new_uv_vtx = true;
                    SDL_assert(sscanf(linebuf, "vt %f %f", &vtx.uv.x, &vtx.uv.y) == 2);
                default:
                    break;
            }
            if (new_pos_vtx) {
                new_pos_vtx = false;
                mVerts.push_back(vtx);
            } else if (vtx_norm_ct == vtx_pos_ct && new_norm_vtx) {
                new_norm_vtx = false;
                mVerts[vtx_pos_ct].norm = vtx.norm;
            } else if (vtx_uv_ct == vtx_pos_ct && new_uv_vtx) {
                new_uv_vtx = false;
                mVerts[vtx_pos_ct].uv = vtx.uv;
            }
        } else if (linebuf[0] == 'f') {
            Face f;
            SDL_assert(sscanf(linebuf, "f %i/%*i/%*i %i/%*i/%*i %i/%*i/%*i", &f.idx0, &f.idx1, &f.idx2) >= 3);
            f.idx0--;
            f.idx1--;
            f.idx2--;
            mFaces.push_back(f);
        }
    }
}
