#pragma once

#include "rws/core/chunk.h"

namespace Rws {

    class String : public Chunk
    {
        RWS_CHUNK(String, ID_STRING, ID_NAOBJECT, RWS_FALSE)

    public:
        Char* string;

        ~String();

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}