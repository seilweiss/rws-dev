#pragma once

#include "rws/core/chunk.h"

namespace Rws {

    class AtomicStruct;

    class Atomic : public Chunk
    {
        RWS_CHUNK(Atomic, ID_ATOMIC, ID_NAOBJECT, RWS_TRUE)

    public:
        AtomicStruct* GetStruct() const { return GetChild<AtomicStruct>(); }
    };

    class AtomicStruct : public Chunk
    {
        RWS_CHUNK(AtomicStruct, ID_STRUCT, ID_ATOMIC, RWS_FALSE)

    public:
        enum Flags
        {
            COLLISIONTEST = 0x1,
            RENDER = 0x4
        };

        Int32 frameIndex;
        Int32 geomIndex;
        Int32 flags;
        Int32 unused;

        Atomic* GetAtomic() const { return GetParentAs<Atomic>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}