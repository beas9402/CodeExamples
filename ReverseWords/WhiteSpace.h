#include "UTF-8Helper.h"

bool isUTF8WhiteSpace(UTF8char& c)
{
    // Reference: https://en.wikipedia.org/wiki/Whitespace_character
    if (c.size == 1)
    {
        switch (c.bytes[0])
        {
        case 0x00: // U+0000 - Null terminator '\0'
        case 0x09: // U+0009 - Tabulation      '\t'
        case 0x0A: // U+000A - Line Feed       '\n'
        case 0x0B: // U+000B - Vertical Tab    '\v'
        case 0x0C: // U+000C - Form Feed       '\f'
        case 0x0D: // U+000D - Carriage return '\r'
        case 0x20: // U+0020 - Space            ' '
            return true;

        default:
            break;
        }
    }
    else if (c.size == 2)
    {
        if (c.bytes[1] == 0x85 || // U+0085 - Next line
            c.bytes[1] == 0xA0)   // U+00A0 - Non-breaking space
        {
            return true;
        }
    }
    else if (c.size == 3)
    {
        switch (c.bytes[0])
        {
        case 0xE1:
            if (c.bytes[1] == 0x94 &&
                c.bytes[2] == 0x80) // U+1680 - Ogham Space Mark
            {
                return true;
            }
            break;
        case 0xE2:
            if (c.bytes[1] == 0x80)
            {
                switch (c.bytes[2])
                {
                case 0x80: // U+2000 - EN Quad
                case 0x81: // U+2001 - EM Quad
                case 0x82: // U+2002 - EN Space
                case 0x83: // U+2003 - EM Space
                case 0x84: // U+2004 - Three-Per-EM Space
                case 0x85: // U+2005 - Four-Per-EM Space
                case 0x86: // U+2006 - Six-Per-EM Space
                case 0x87: // U+2007 - Figure Space
                case 0x88: // U+2008 - Punctuation Space
                case 0x89: // U+2009 - Thin Space
                case 0x8A: // U+200A - Hair Space
                case 0xA8: // U+2028 - Line Separator
                case 0xA9: // U+2029 - Paragraph Separator
                case 0xAF: // U+202F - Narrow No-Break Space
                    return true;
                default:
                    break;
                }
            }
            if (c.bytes[1] == 0x81 &&
                c.bytes[2] == 0x9F) // U+205F - Medium Mathematical Space
            {
                return true;
            }
            break;
        case 0xE3:
            if (c.bytes[1] == 0x80 &&
                c.bytes[2] == 0x80) // U+3000 - Ideographic Space
            {
                return true;
            }
            break;
        default:
            break;
        } // end switch
    } // end if 3 Bytes

    // All other codepoints are not whitespace (including 4 byte UTF-8 codepoints)
    return false;
}