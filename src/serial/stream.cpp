#include "stream.h"
#include <cstdio>

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

int FileStream::ReadImpl(void* out, int len) {
    return fread(out, len, 1, mFileObj);
}

int FileStream::WriteImpl(const void* in, int len) {
    return fwrite(in, len, 1, mFileObj);
}
