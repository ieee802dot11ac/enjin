/**
 * @file vec.h
 * @author ieee 802.11ac
 * @brief Vector classes.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

#include <SDL2/SDL_assert.h>

template <int T>
class Vector {
    public:
    float flt[T];

    Vector() : flt() {}
    float operator[](int i) { SDL_assert(i < T); return ((float*)this)[i]; }
    operator float*() { return ((float*)this); }

    Vector& operator +=(float diff) { for (float& f : flt) f += diff; return *this; }
    Vector& operator -=(float diff) { for (float& f : flt) f -= diff; return *this; }
};
