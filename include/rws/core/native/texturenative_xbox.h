#pragma once

#include "rws/core/native/texturenative_platform.h"
#include "rws/core/core_common.h"

#include <string>

namespace Rws {

    class TextureNativeXbox : public TextureNativePlatform
    {
        RWS_TEXTURENATIVEPLATFORM(TextureNativeXbox, ID_XBOX, 0x00000005)

    public:
        Int32 dxtCompression;

        void Read(Stream* stream, UInt32 length, TextureNative* textureNative) override;
        void Write(Stream* stream, TextureNative* textureNative);
    };

}