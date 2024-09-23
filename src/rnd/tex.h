/**
 * @file tex.h
 * @author ieee 802.11ac
 * @brief Base texture class.
 * @version 0.1
 * @date 2024-09-22
 * 
 */

#pragma once

#include "interfaces/loadable.h"
#include <stdint.h>

class Texture : public ILoadable {
    public:
    enum PixelFmt { // good enough for now!
        kRGB_f  = 0b0000,
        kRGBA_f = 0b0001,
        kRGB_c  = 0b0010,
        kRGBA_c = 0b0011
    };

    Texture();
    virtual ~Texture();
    virtual void Load(Stream&);
    virtual void Save(Stream&);

    void UploadToVRAM();
    private:

    uint16_t mWidth, mHeight;
    PixelFmt mFormat;
    void* mData; // note: includes mipmaps (use LineSize * mHeight to get cur. mip size)

    public:
    uint32_t LineSize() { 
        if ((uint32_t)mFormat & 2) {
            return (kRGB_c ? 3 : 4) * mWidth;
        }
        else return (kRGB_f ? 12 : 16) * mWidth;
    }
};
