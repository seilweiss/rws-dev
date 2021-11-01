#pragma once

#include "nativedata_platform.h"

namespace Rws {

    class NativeDataPS2 : public NativeDataPlatform
    {
        RWS_NATIVEDATAPLATFORM(NativeDataPS2, ID_PS2)

    public:
        void Read(Stream* stream, UInt32 length, NativeData* nativeData) override;
        void Write(Stream* stream, NativeData* nativeData);
    };

}