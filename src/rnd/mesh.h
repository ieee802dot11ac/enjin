/**
 * @file mesh.h
 * @author ieee 802.11ac
 * @brief Currently: loads text files into vec3 vectors. Later: mesh class.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

#include "math/vec.h"
#include "interfaces/loadable.h"
#include <vector>

std::vector<Vector3> load_mesh(const char* filename);

class Mesh : public Loadable {

};
