#include "rws/core/chunk_unicodestring.h"

#include <cstdlib>

namespace Rws {

    namespace {

        UInt32 GetStringSize(const Char* string)
        {
            return ((((strlen(string) + 1) * sizeof(Char)) + 3) & ~3);
        }

    }

    UnicodeString::~UnicodeString()
    {
        if (string)
        {
            free(string);
        }
    }

    void UnicodeString::Read(Stream* stream, UInt32 length)
    {
        string = (Char*)malloc(length);

        if (string)
        {
            unsigned short unicodeString[64];
            Char* baseString = string;

            while (length > 0)
            {
                UInt32 bytesToRead = (length > 128) ? 128 : length;
                UInt32 charCount = bytesToRead >> 1;

                stream->Read(unicodeString, bytesToRead);

                length -= bytesToRead;

                for (UInt32 i = 0; i < charCount; i++)
                {
                    baseString[i] = (Char)unicodeString[i];
                }

                baseString += charCount;
            }
        }
    }

    void UnicodeString::Write(Stream* stream)
    {
        const Char* str = (string != RWS_NULL) ? string : "";
        UInt32 length = GetStringSize(string);
        stream->Write(str, length);
    }

}