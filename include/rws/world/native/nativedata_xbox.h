#pragma once

#include "nativedata_platform.h"

namespace Rws {

    class NativeDataXbox : public NativeDataPlatform
    {
        RWS_NATIVEDATAPLATFORM(NativeDataXbox, ID_XBOX)

    public:
        void Read(Stream* stream, UInt32 length, NativeData* nativeData) override;
        void Write(Stream* stream, NativeData* nativeData);
    };

}