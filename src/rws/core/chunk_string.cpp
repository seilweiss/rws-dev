#include "rws/core/chunk_string.h"

#include <cstdlib>

namespace Rws {

    namespace {

        UInt32 GetStringSize(const Char* string)
        {
            return ((((strlen(string) + 1) * sizeof(Char)) + 3) & ~3);
        }

    }

    String::~String()
    {
        if (string)
        {
            free(string);
        }
    }

    void String::Read(Stream* stream, UInt32 length)
    {
        string = (Char*)malloc(length * sizeof(Char));

        if (string)
        {
            char multiByteString[64];
            Char* baseString = string;

            while (length > 0)
            {
                UInt32 bytesToRead = (length > 64) ? 64 : length;

                stream->Read(multiByteString, bytesToRead);

                length -= bytesToRead;

                for (UInt32 i = 0; i < bytesToRead; i++)
                {
                    baseString[i] = (Char)multiByteString[i];
                }

                baseString += bytesToRead;
            }
        }
    }

    void String::Write(Stream* stream)
    {
        const Char* str = (string != RWS_NULL) ? string : "";
        UInt32 length = GetStringSize(str);
        stream->Write(str, length);
    }

}