#pragma once

#include "rws/world/native/nativedata_platform.h"
#include "rws/core/byte_array.h"

namespace Rws {

    class NativeDataDefault : public NativeDataPlatform
    {
        RWS_NATIVEDATAPLATFORM(NativeDataDefault, ID_NAPLATFORM)

    public:
        ByteArray byteArray;

        void Read(Stream* stream, UInt32 length, NativeData* nativeData) override { byteArray.Read(stream, length); }
        void Write(Stream* stream, NativeData* nativeData) override { byteArray.Write(stream); }
    };

}