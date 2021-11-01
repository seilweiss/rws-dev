#pragma once

#include "rws/core/chunk.h"

namespace Rws {

    class UnicodeString : public Chunk
    {
        RWS_CHUNK(UnicodeString, ID_UNICODESTRING, ID_NAOBJECT, RWS_FALSE)

    public:
        Char* string;

        ~UnicodeString();

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}