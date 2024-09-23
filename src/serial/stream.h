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
#include <arpa/inet.h> // for ntoh*
#include <memory>
#include "types.h"

#define IS_BIG_ENDIAN (ntohs(0xABCD) == 0xABCD) // TODO replace with compile-time define

class Stream {
    protected:
    bool mFail;
    public:
    Stream() {}
    virtual ~Stream() {}
    virtual bool Fail() { return false; }
    virtual int Read(void* data, int len) = 0;
    virtual int Write(const void* data, int len) = 0;

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

    LOAD(Vector2)
    LOAD(Vector3)
    LOAD(Vector4)
    SAVE(Vector2)
    SAVE(Vector3)
    SAVE(Vector4)

    // requires more smarts than blind R/Ws due to implementation specifics
    Stream& operator>>(Matrix& in); 
    Stream& operator<<(const Matrix in);
    
    Stream& operator>>(std::string& str);
    Stream& operator<<(const std::string str);

    template <typename T> Stream& operator>>(std::shared_ptr<T>& in) {
        class ILoadable* ldbl = dynamic_cast<class ILoadable*>(in.get()); // cause concepts are nonsense
        if (ldbl != NULL) {
            *this >> ldbl->mFilename;
        }
    }
    template <typename T> Stream& operator<<(const std::shared_ptr<T>& in) {
        class ILoadable* ldbl = dynamic_cast<class ILoadable*>(in.get());
        if (ldbl != NULL) {
            *this << ldbl->mFilename;
        }
    }

    #undef LOAD
    #undef SAVE
};

class FileStream : public Stream {
    public:
    FileStream(const char* filename, bool ro);
    virtual ~FileStream();
    virtual bool Fail();
    virtual int Read(void* data, int len);
    virtual int Write(const void* data, int len);

    private:
    FILE* mFileObj;
};
