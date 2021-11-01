#pragma once

#include "rws/core/types.h"

namespace Rws {

    enum Endian
    {
        LITTLE_ENDIAN,
        BIG_ENDIAN
    };

    class Mem
    {
    public:
        static Endian GetNativeEndian() { return m_nativeEndian; }

        static void* Swap16(void* mem, UInt32 size);
        static void* Swap32(void* mem, UInt32 size);
        static void* LittleEndian16(void* mem, UInt32 size);
        static void* LittleEndian32(void* mem, UInt32 size);
        static void* BigEndian16(void* mem, UInt32 size);
        static void* BigEndian32(void* mem, UInt32 size);

    private:
        static Endian m_nativeEndian;
    };

}