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
#include "math/vec.h"
#include <vector>

struct Vertex {
    public:
    Vector<3> pos;
    Vector<3> norm;
    Vector<2> uv;
    Vector<4> col;

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

class Mesh : public Loadable, public Drawable {
public:
    Mesh();
    virtual ~Mesh();
    virtual void Load(Stream&);
    virtual void Save(Stream&);
    virtual void Draw();
//private:
    std::vector<Vertex> mVerts;
    std::vector<Face> mFaces;
public:

    static int sRevision;
};
