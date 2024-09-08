/**
 * @file loadable.h
 * @author ieee 802.11ac
 * @brief Interface for all loadable classes.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

#include "serial/stream.h"

class Loadable {
    public:
    Loadable() {}
    virtual ~Loadable() {}
    virtual void Load(Stream&) = 0;
    virtual void Save(Stream&) = 0;
};
