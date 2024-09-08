/**
 * @file drawable.h
 * @author ieee 802.11ac
 * @brief Interface for all drawable classes.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

class Drawable {
    public:
    Drawable() {}
    virtual ~Drawable() {}
    virtual void Draw() = 0;
};
