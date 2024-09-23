/**
 * @file loadable.h
 * @author ieee 802.11ac
 * @brief Interface for all loadable classes.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

#include <string>

class Stream; // forward decl

class ILoadable {
    public:
    ILoadable() {}
    virtual ~ILoadable() {}
    virtual void Load(Stream&) = 0;
    virtual void Save(Stream&) = 0;

    std::string mFilename;
};
