#include "rws/core/mem.h"

namespace Rws {

    namespace {

        Endian GetSystemEndian()
        {
            Int32 x = 1;

            if (*(UInt8*)&x == 1)
            {
                return LITTLE_ENDIAN;
            }
            else
            {
                return BIG_ENDIAN;
            }
        }

    }

    Endian Mem::m_nativeEndian = GetSystemEndian();

    void* Mem::Swap16(void* mem, UInt32 size)
    {
        UInt16* x = (UInt16*)mem;

        while (size)
        {
            *x = (*x >> 8) | (*x << 8);
            x++;
            size -= 2;
        }

        return mem;
    }

    void* Mem::Swap32(void* mem, UInt32 size)
    {
        UInt32* x = (UInt32*)mem;

        while (size)
        {
            *x = ((*x >> 24) & 0xff) | ((*x << 8) & 0xff0000) | ((*x >> 8) & 0xff00) | ((*x << 24) & 0xff000000);
            x++;
            size -= 4;
        }

        return mem;
    }

    void* Mem::LittleEndian16(void* mem, UInt32 size)
    {
        if (m_nativeEndian == BIG_ENDIAN)
        {
            return Swap16(mem, size);
        }
        else
        {
            return mem;
        }
    }

    void* Mem::LittleEndian32(void* mem, UInt32 size)
    {
        if (m_nativeEndian == BIG_ENDIAN)
        {
            return Swap32(mem, size);
        }
        else
        {
            return mem;
        }
    }

    void* Mem::BigEndian16(void* mem, UInt32 size)
    {
        if (m_nativeEndian == LITTLE_ENDIAN)
        {
            return Swap16(mem, size);
        }
        else
        {
            return mem;
        }
    }

    void* Mem::BigEndian32(void* mem, UInt32 size)
    {
        if (m_nativeEndian == LITTLE_ENDIAN)
        {
            return Swap32(mem, size);
        }
        else
        {
            return mem;
        }
    }

}