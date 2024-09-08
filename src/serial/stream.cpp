#include "stream.h"
#include <cstdio>

Stream::~Stream() {}

FileStream::FileStream(const char* filename, bool ro) {
    mFileObj = fopen(filename, ro ? "rb" : "ab+");
}

FileStream::~FileStream() {
    fclose(mFileObj);
}

int FileStream::ReadImpl(void* out, int len) {
    return fread(out, len, 1, mFileObj);
}

int FileStream::WriteImpl(const void* in, int len) {
    return fwrite(in, len, 1, mFileObj);
}
