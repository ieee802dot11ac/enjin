#include "mesh.h"
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>

int Mesh::sRevision = 0;
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
    }
}

void Mesh::ImportOBJ(std::ifstream strm) {
    char linebuf[256] = {0};
    while (!strm.fail()) {
        strm.getline(linebuf, 256);
        if (linebuf[0] == 'v') {
            Vertex vtx;
            switch (linebuf[1]) {
                case ' ':
                    SDL_assert(sscanf(linebuf, "v %f %f %f", &vtx.pos.x, &vtx.pos.y, &vtx.pos.z) == 3);
                    break;
                case 'n':
                    SDL_assert(sscanf(linebuf, "vn %f %f %f", &vtx.norm.x, &vtx.norm.y, &vtx.norm.z) == 3);
                    break;
                case 't':
                    SDL_assert(sscanf(linebuf, "vt %f %f", &vtx.uv.x, &vtx.uv.y) == 2);
                default:
                    break;
            }
            mVerts.push_back(vtx);
        } else if (linebuf[0] == 'f') {
            Face f;
            SDL_assert(sscanf(linebuf, "f %i/ / %i/ / %i/ / ", &f.idx0, &f.idx1, &f.idx2) >= 3);
            mFaces.push_back(f);
        }
    }
}
