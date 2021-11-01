#pragma once

#include "rws/core/chunk.h"
#include "rws/core/byte_array.h"

namespace Rws {

    class DefaultChunk : public Chunk
    {
        RWS_CHUNK(DefaultChunk, ID_NAOBJECT, ID_NAOBJECT, RWS_FALSE)

    public:
        ByteArray byteArray;

        void Read(Stream* stream, UInt32 length) override { byteArray.Read(stream, length); }
        void Write(Stream* stream) override { byteArray.Write(stream); }
    };

}