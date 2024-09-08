/**
 * @file vec.h
 * @author ieee 802.11ac
 * @brief Vector classes.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

class Vector3 {
    private:
    float x, y, z;
    public:
    constexpr float& X() { return x; }
    constexpr float& Y() { return y; }
    constexpr float& Z() { return z; }

    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3() : x(0), y(0), z(0) {}
    float operator[](int i) { return ((float*)this)[i]; }
    operator float*() { return ((float*)this); }
};
