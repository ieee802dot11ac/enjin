/**
 * @file mesh.h
 * @author ieee 802.11ac
 * @brief Mesh class.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

#include "interfaces/drawable.h"
#include "interfaces/loadable.h"
#include "serial/stream.h"
#include "types.h"
#include <fstream>
#include <vector>

struct Vertex {
    public:
    Vector3 pos;
    Vector3 norm;
    Vector2 uv;
    Vector4 col;

    void Load(Stream&);
    void Save(Stream&);
};

struct Face {
    public:
    Face() : idx0(0), idx1(0), idx2(0) {}
    Face(int i0, int i1, int i2) : idx0(i0), idx1(i1), idx2(i2) {}
    int idx0, idx1, idx2;
    void Load(Stream& strm) { strm >> idx0 >> idx1 >> idx2; }
    void Save(Stream& strm) { strm << idx0 << idx1 << idx2; }
};

class Mesh : public ILoadable, public IDrawable {
public:
    Mesh();
    virtual ~Mesh();
    virtual void Load(Stream&);
    virtual void Save(Stream&);
    virtual void Draw();

    void ImportOBJ(std::ifstream);
//private:
    std::vector<Vertex> mVerts;
    std::vector<Face> mFaces;
public:

    static int sRevision;
};
