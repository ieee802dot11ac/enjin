#include "stream.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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

Stream& Stream::operator>>(std::string& str) {
    uint32_t len;
    *this >> len;
    str.reserve(len);
    for (int i = 0; i < len; i++) {
        int8_t c;
        *this >> c;
        str.push_back(c);
    }
    return *this;
}

Stream& Stream::operator<<(const std::string str) {
    *this << (uint32_t)str.length();
    for (char c : str) *this << c;
    return *this;
}


FileStream::FileStream(const char* filename, bool ro) {
    mFileObj = fopen(filename, ro ? "rb" : "wb+");
    if (mFileObj == NULL) throw std::runtime_error("Cannot open file");
}

FileStream::~FileStream() {
    fclose(mFileObj);
}

bool FileStream::Fail() {
    mFail = feof(mFileObj) | ferror(mFileObj);
    return mFail;
}

int FileStream::Read(void* data, int len) {
    return fread(data, len, 1, mFileObj);
}

int FileStream::Write(const void* data, int len) {
    return fwrite(data, len, 1, mFileObj);
}
