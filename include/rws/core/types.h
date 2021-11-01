#pragma once

#include <cstdint>

namespace Rws {

    typedef int8_t Int8;
    typedef uint8_t UInt8;
    typedef int16_t Int16;
    typedef uint16_t UInt16;
    typedef int32_t Int32;
    typedef uint32_t UInt32;
    typedef char Char;
    typedef float Real;
    typedef Int32 Bool;

    static_assert(sizeof(Int8) == 1, "sizeof(Int8) != 1");
    static_assert(sizeof(UInt8) == 1, "sizeof(UInt8) != 1");
    static_assert(sizeof(Int16) == 2, "sizeof(Int16) != 2");
    static_assert(sizeof(UInt16) == 2, "sizeof(UInt16) != 2");
    static_assert(sizeof(Int32) == 4, "sizeof(Int32) != 4");
    static_assert(sizeof(UInt32) == 4, "sizeof(UInt32) != 4");
    static_assert(sizeof(Char) == 1, "sizeof(Char) != 1");
    static_assert(sizeof(Real) == 4, "sizeof(Real) != 4");
    static_assert(sizeof(Bool) == 4, "sizeof(Bool) != 4");

}

#define RWS_TRUE 1
#define RWS_FALSE 0
#define RWS_NULL 0