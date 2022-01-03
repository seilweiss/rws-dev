#pragma once

#include "rws/core/chunk.h"
#include "rws/core/core_common.h"

namespace Rws {

    class TextureNativePlatform;
    class TextureNativeStruct;

    class TextureNative : public Chunk
    {
        RWS_CHUNK(TextureNative, ID_TEXTURENATIVE, ID_NAOBJECT, RWS_TRUE)

    public:
        TextureFilterMode filtering;
        TextureAddressMode addressingU;
        TextureAddressMode addressingV;
        Char name[32];
        Char maskName[32];
        RasterFormat rasterFormat;
        Bool hasAlpha;
        UInt32 width;
        UInt32 height;
        UInt32 depth;
        std::vector<RGBA> texels;

        typedef TextureNativePlatform* (*PlatformConstructor)();

        static void RegisterPlatformType(UInt32 platformID, UInt32 magic, PlatformConstructor constructor);
        static void UnregisterPlatformType(UInt32 platformID);
        static void ClearPlatformTypes();
        static TextureNativePlatform* CreatePlatformData(UInt32 platformID);

        TextureNativeStruct* GetStruct() const { return GetChild<TextureNativeStruct>(); }
    };

    class TextureNativeStruct : public Chunk
    {
        RWS_CHUNK(TextureNativeStruct, ID_STRUCT, ID_TEXTURENATIVE, RWS_FALSE)

    public:
        UInt32 platformID = ID_NAPLATFORM;

        ~TextureNativeStruct();

        TextureNative* GetTextureNative() const { return GetParentAs<TextureNative>(); }

        TextureNativePlatform* GetPlatformData() const { return m_platform; }
        void CreatePlatformData();

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;

    private:
        TextureNativePlatform* m_platform = RWS_NULL;
    };

}