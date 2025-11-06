// ReverseWords.cpp : Defines the entry point for the application.
//
#include <iostream>

#include "ReverseBytes.h"
#include "Whitespace.h"

//using UTF8 = uint;

void reverseWords(Byte* str)
{
    int wordstart{0};
    UTF8char current;
    bool done = false;
    for (int i = 0; done == false; i += current.size)
    {
        Byte* current_addr = str + i;
        current.set(current_addr);
        if (isUTF8WhiteSpace(current))
        {
            int length = i - wordstart;
            reverseBytes(str + wordstart, length);
            wordstart = i + 1;
        }
        else if (current.size > 1)
        {
            // prereverse bytes of any multibyte character
            // so that when we reverse the entire word it will
            // put the multibyte character back in the right order and spot
            reverseBytes(current_addr, current.size);
        }

        // check for done here to allow last word to reverse
        if (current.bytes[0] == '\0')
        {
            done = true;
        }
    }
}

int main()
{

    Byte helloworld[128]{ u8"Hello CMake. w🚀hat " };
    std::cout << helloworld << std::endl;
    reverseWords(helloworld);
    std::cout << helloworld << std::endl;

    return 0;
}



