/**
 * @file drawable.h
 * @author ieee 802.11ac
 * @brief Interface for all drawable classes.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

class IDrawable {
    public:
    IDrawable() {}
    virtual ~IDrawable() {}
    virtual void Draw() = 0;
};
