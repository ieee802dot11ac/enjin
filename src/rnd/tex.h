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
#include <queue>
#include <stdint.h>

#define MAX_TEXES 256

class Texture : public ILoadable {
    public:
    enum PixelFmt { // good enough for now!
        kRGB_f  = 0b0000,
        kRGBA_f = 0b0001,
        kRGB_c  = 0b0100,
        kRGBA_c = 0b0101
    };

    Texture();
    Texture(uint16_t width, uint16_t height, PixelFmt);
    virtual ~Texture();
    virtual void Load(Stream&);
    virtual void Save(Stream&);

    /// Called once after initializing data.
    void UploadToVRAM();

    /// Called whenever a texture needs to be set active in the OGL state.
    void SetActiveTexture();

    static void Init();
    private:

    uint16_t mWidth, mHeight;
    PixelFmt mFormat;
    void* mData;
    uint32_t mOpenGLName;

    static std::queue<uint32_t> sTexNames;
};
