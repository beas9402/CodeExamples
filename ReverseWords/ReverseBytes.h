#pragma once
#include <cstdint>

using Byte = uint8_t; 

void reverseBytes(Byte* bytePtr, int length=0)
{
    if (length == 0)
    {
        length = (int)strlen((char *)bytePtr);
    }

    static Byte swap;
    int left = 0;
    int right = length - 1;

    while (left < right)
    {
        swap = bytePtr[left];
        bytePtr[left] = bytePtr[right];
        bytePtr[right] = swap;
        left++;
        right--;
    }
}