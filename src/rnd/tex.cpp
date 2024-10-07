#include "tex.h"
#include <SDL2/SDL_opengl.h>

std::queue<uint32_t> Texture::sTexNames;

Texture::Texture() : mWidth(0), mHeight(0), mData(NULL), mFormat(kRGB_f), mOpenGLName(0) {}

Texture::Texture(uint16_t width, uint16_t height, PixelFmt format) : 
    mWidth(width), 
    mHeight(height), 
    mFormat(format), 
    mData(NULL), 
    mOpenGLName(0) {

}

Texture::~Texture() {

}

void Texture::Init() {
    uint32_t name_buf[256];
    glGenTextures(MAX_TEXES, name_buf);
    for (uint32_t name : name_buf) sTexNames.push(name);
}

void Texture::UploadToVRAM() {
    mOpenGLName = sTexNames.front();
    sTexNames.pop();
    SetActiveTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_BYTE, mData);
}

void Texture::SetActiveTexture() {
    glBindTexture(GL_TEXTURE_2D, mOpenGLName);
}
