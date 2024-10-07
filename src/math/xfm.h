/**
 * @file xfm.h
 * @author ieee 802.11ac
 * @brief Transform class for positionable objects.
 * @version 0.1
 * @date 2024-10-06
 * 
 */

#pragma once

#include "types.h"

struct Transform {
    Vector3 pos;
    Matrix rot;

    Transform();
    
};
