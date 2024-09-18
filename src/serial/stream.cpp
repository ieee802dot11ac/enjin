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

int FileStream::_ReadLE(void* data, int len) {

}

int FileStream::_ReadBE(void* data, int len) {

}

int FileStream::_WriteLE(const void* data, int len) {

}

int FileStream::_WriteBE(const void* data, int len) {

}

