#pragma once

#include <bit>
#include "ReverseBytes.h"

using Byte = uint8_t;
#define Max_UTF8_Bytes 4

int UTF8size(const Byte& leadbyte)
{
    // Reference: https://en.wikipedia.org/wiki/UTF-8
    if (leadbyte < 0x80) { return 1; } // ASCII equivalents
    if (leadbyte < 0xC0) { return 0; } // Continuation byte
    if (leadbyte > 0xC1)
    {
        if (leadbyte < 0xE0) { return 2; }
        if (leadbyte < 0xF0) { return 3; }
        if (leadbyte < 0xF5) { return 4; }
    }

    // 0xC0, 0xC1, and 0xF5-0xFF are unused in UTF-8
    return -1; // Invalid UTF-8 lead byte
}

struct UTF8char
{
    int size;
    union // using a union here to make it easy to set all bytes at the same time
    {
        uint32_t allbytes;
        Byte bytes[Max_UTF8_Bytes];
    };
    void set(Byte* bytePtr)
    {
        allbytes = 0x0;
        size = UTF8size(bytePtr[0]);
        if (size > 0 and size <= Max_UTF8_Bytes)
        {
            for (int i = 0; i < size; i++)
            {
                bytes[i] = bytePtr[i];
            }
        }
    }
    // default constructor
    UTF8char() : size{ 0 }, allbytes{ 0 } {}
    // a couple of handy contructors
    UTF8char(Byte* bytePtr)
    {
        set(bytePtr);
    }

    // allows things like UTF8char(0x20 << 24)
    UTF8char(uint32_t * ptr)
    {
        allbytes = *ptr;
        // check for little endian, we will need to swap the bytes
        if constexpr (std::endian::native == std::endian::little)
        {
            reverseBytes(bytes, 4);
        }
        size = UTF8size(bytes[0]);
    }
};
