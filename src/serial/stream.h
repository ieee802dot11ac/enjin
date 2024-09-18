/**
 * @file stream.h
 * @author ieee 802.11ac
 * @brief Binary stream for loading files.
 * @version 0.1
 * @date 2024-09-07
 * 
 */

#pragma once

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <arpa/inet.h>
#include "math/vec.h"

#define IS_BIG_ENDIAN (ntohs(0xABCD) == 0xABCD) // TODO replace with compile-time define

class Stream {
    virtual int Read(void* data, int len) { return (len > 1 && IS_BIG_ENDIAN) ? _ReadBE(data, len) : _ReadLE(data, len); }
    virtual int Write(const void* data, int len) { return (len > 1 && IS_BIG_ENDIAN) ? _WriteBE(data, len) : _WriteLE(data, len); }
    virtual int _ReadLE(void* data, int len) = 0;
    virtual int _ReadBE(void* data, int len) = 0;
    virtual int _WriteLE(const void* data, int len) = 0;
    virtual int _WriteBE(const void* data, int len) = 0;
    protected:
    bool mFail;
    public:
    Stream() {}
    virtual ~Stream() {}
    virtual bool Fail() { return false; }

    #define LOAD(type) Stream& operator>>(type& in) { if (!Fail()) Read(&in, sizeof(type)); return *this; }
    #define SAVE(type) Stream& operator<<(type in) { if (!Fail()) Write(&in, sizeof(type)); return *this; }
    
    LOAD(uint8_t)
    LOAD(int8_t)
    LOAD(uint16_t)
    LOAD(int16_t)
    LOAD(uint32_t)
    LOAD(int32_t)
    LOAD(uint64_t)
    LOAD(int64_t)
    LOAD(float_t)
    LOAD(double_t)
    SAVE(uint8_t)
    SAVE(int8_t)
    SAVE(uint16_t)
    SAVE(int16_t)
    SAVE(uint32_t)
    SAVE(int32_t)
    SAVE(uint64_t)
    SAVE(int64_t)
    SAVE(float_t)
    SAVE(double_t)

    template <int T>
    Stream& operator>>(Vector<T>& vec) { for (float& f : vec.flt) *this >> f; return *this; }

    template <int T>
    Stream& operator<<(Vector<T>& vec) { for (float f : vec.flt) *this << f; return *this; }

    #undef LOAD
    #undef SAVE
};

class FileStream : public Stream {
    public:
    FileStream(const char* filename, bool ro);
    virtual ~FileStream();
    virtual bool Fail();

    private:
    virtual int _ReadLE(void* data, int len);
    virtual int _ReadBE(void* data, int len);
    virtual int _WriteLE(const void* data, int len);
    virtual int _WriteBE(const void* data, int len);

    FILE* mFileObj;
};
