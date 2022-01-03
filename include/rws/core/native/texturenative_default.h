#pragma once

#include "rws/core/native/texturenative_platform.h"
#include "rws/core/byte_array.h"

namespace Rws {

    class TextureNativeDefault : public TextureNativePlatform
    {
        RWS_TEXTURENATIVEPLATFORM(TextureNativeDefault, ID_NAPLATFORM, 0)

    public:
        ByteArray byteArray;

        void Read(Stream* stream, UInt32 length, TextureNative* textureNative) override { byteArray.Read(stream, length); }
        void Write(Stream* stream, TextureNative* textureNative) override { byteArray.Write(stream); }
    };

}