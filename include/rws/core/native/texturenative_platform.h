#pragma once

#include "rws/core/stream.h"
#include "rws/core/chunk_texturenative.h"

#define RWS_TEXTURENATIVEPLATFORM(ClassName, platformID, magic)\
    public:\
        static void Register() { Rws::TextureNative::RegisterPlatformType((platformID), (magic), [] { return (TextureNativePlatform*)new ClassName; }); }\
        static void Unregister() { Rws::TextureNative::UnregisterPlatformType((platformID)); }\
        static const char* GetNameStatic() { return #ClassName; }\
        static UInt32 GetPlatformIDStatic() { return (platformID); }\
        static UInt32 GetMagicStatic() { return (magic); }\
        virtual const char* GetName() const { return #ClassName; }\
        virtual UInt32 GetPlatformID() const { return (platformID); }\
        virtual UInt32 GetMagic() const { return (magic); }

namespace Rws {

    class TextureNativePlatform
    {
        RWS_TEXTURENATIVEPLATFORM(TextureNativePlatform, ID_NAPLATFORM, 0)

    public:
        virtual void Read(Stream* stream, UInt32 length, TextureNative* textureNative) {}
        virtual void Write(Stream* stream, TextureNative* textureNative) {}
    };

}