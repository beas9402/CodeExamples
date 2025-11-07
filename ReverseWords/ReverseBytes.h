#pragma once
#include <cstdint>

inline void reverseBytes(uint8_t* bytePtr, size_t length)
{
    // only swap if at least 2 bytes
    if (length >= 2)
    {
        static uint8_t swap;
        size_t left = 0;
        size_t right = length - 1;

        while (left < right)
        {
            swap = bytePtr[left];
            bytePtr[left] = bytePtr[right];
            bytePtr[right] = swap;
            left++;
            right--;
        }
    }
}
