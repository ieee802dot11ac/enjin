#include "mesh.h"
#include <fstream>

std::vector<Vector3> load_mesh(const char* filename) {
    std::vector<Vector3> mesh;
    std::ifstream file(filename);
    while (!file.eof() && !file.fail()) {
        Vector3 vec;
        file >> vec.X();
        file >> vec.Y();
        file >> vec.Z();
        mesh.push_back(vec);
    }
    return mesh;
}
