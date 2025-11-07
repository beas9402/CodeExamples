//
// In an interview, I was asked to reverse each 'word' in an string.
// A 'word' being defined as a group a characters separated by whitespace.
// Assume that a func 'bool isWhiteSpace(char*)' is already written.
// Also assume that this is a memory constrained system with no available libraries.
//     Before: "Hello World, this is a test!"
//     After:  "olleH ,dlroW siht si a !tset"
// This was a pretty normal thing, but then after the interview I
// wondered how to do this when UTF-8 (multi-byte) characters are in the string

#include <iostream>
#include "ReverseBytes.h" // reverse raw (uint8_t) bytes
#include "Whitespace.h"   // for isUTF8WhiteSpace(Byte*)

// This is my attempt to reverse words when the string contains UTF-8.
// I know that there are better opensource projects out there, but I enjoyed figuring this out.
//
// This works okay except when UTF-8 'combining characters' are used. (my next project?)
void reverseWords(Byte* str)
{
    size_t wordstart{0};
    UTF8char current;
    bool done = false;
    for (size_t i = 0; done == false; i += current.size)
    {
        Byte* current_addr = str + i;
        current.set(current_addr);
        if (isUTF8WhiteSpace(current))
        {
            size_t length = i - wordstart;
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

int testnumber = 0;
bool test_reverse_words(Byte* str, const Byte* expected, size_t bytecount)
{
    testnumber++;
    std::cout << "TEST " << testnumber << ":" << std::endl;
    std::cout << "  Test String : '" << u8out(str) << "'" << std::endl;
    std::cout << "  Expecting   : '" << u8out(expected) << "'" << std::endl;
    reverseWords(str);
    std::cout << "  reverseWords: '" << u8out(str) << "'" << std::endl;

    bool match = std::char_traits<char8_t>::compare(str, expected, bytecount) == 0;
    if (match)
    {
        std::cout << "    Pass" << std::endl;
    }
    else
    {
        std::cout << "    FAILED" << std::endl;
    }
    std::cout << std::endl;
    return match;
}

// to make writing tests easier
# define TEST_REVERSE(teststr, expected) { Byte buffer[sizeof(teststr)] {teststr}; test_reverse_words(buffer, expected, sizeof(expected)); }

int main()
{
    // on Windows this is needed to properly display UTF-8 in a console app
    turnOnUTF8Console();

    // This test will pass 
    TEST_REVERSE(
        u8"Hello World. w🚀hat ",
        u8"olleH .dlroW tah🚀w "
    );

    // This test will fail because 🏳️‍🌈 is made with combining chars
    // when reversed with my current code 🏳️‍🌈 turns into '🌈‍️🏳'
    TEST_REVERSE(
        u8"abcd 🚀🏳️‍🌈 xyz",
        u8"dcba 🏳️‍🌈🚀 zyx"
    );
}



