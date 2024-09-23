#include "stream.h"
#include <SDL2/SDL_assert.h>
#include <algorithm>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int Stream::Read(void* data, int len) { 
    if (len > 1 && IS_BIG_ENDIAN) {
        return _ReadBE(data, len); 
    } else return _ReadLE(data, len); 
}

int Stream::Write(const void* data, int len) { 
    if (len > 1 && IS_BIG_ENDIAN) {
        return _WriteBE(data, len);
    } else return _WriteLE(data, len); 
}

Stream& Stream::operator>>(Matrix& in) {
    uint32_t w,h;
    *this >> w >> h;
    Matrix mtx(w,h);

    for (int i = 0; i != h; i++) { // NOTE: when saved, this goes row-row-row, not col-col-col
        for (int j = 0; j != w; j++) {
            float tmp;
            *this >> tmp;
            mtx.get_mut(j, i) = tmp;
        }
    }

    in = mtx;
    return *this;
}

Stream& Stream::operator<<(const Matrix in) {
    *this << in.width << in.height;
    for (int i = 0; i != in.height; i++) {
        for (int j = 0; j != in.width; j++) {
            *this << in.get(j,i);
        }
    }
    return *this;
}

FileStream::FileStream(const char* filename, bool ro) {
    mFileObj = fopen(filename, ro ? "rb" : "wb+");
}

FileStream::~FileStream() {
    fclose(mFileObj);
}

bool FileStream::Fail() {
    mFail = feof(mFileObj) | ferror(mFileObj);
    return mFail;
}

int FileStream::_ReadLE(void* data, int len) {
    uint8_t buf[len];
    size_t ret = fread(buf, len, 1, mFileObj);
    if (IS_BIG_ENDIAN) {
        SDL_assert(len % 2 != 1);
        std::reverse(buf, buf + len);
    }
    memcpy(data, buf, len);
    return ret;
}

int FileStream::_ReadBE(void* data, int len) {
    uint8_t buf[len];
    size_t ret = fread(buf, len, 1, mFileObj);
    if (!IS_BIG_ENDIAN) {
        SDL_assert(len % 2 != 1);
        std::reverse(buf, buf + len);
    }
    memcpy(data, buf, len);
    return ret;
}

int FileStream::_WriteLE(const void* data, int len) {
    uint8_t buf[len];
    memcpy(buf, data, len);
    if (IS_BIG_ENDIAN) {
        SDL_assert(len % 2 != 1);
        std::reverse(buf, buf + len);
    }
    return fwrite(buf, len, 1, mFileObj);
}

int FileStream::_WriteBE(const void* data, int len) {
    uint8_t buf[len];
    memcpy(buf, data, len);
    if (!IS_BIG_ENDIAN) {
        SDL_assert(len % 2 != 1);
        std::reverse(buf, buf + len);
    }
    return fwrite(buf, len, 1, mFileObj);
}

