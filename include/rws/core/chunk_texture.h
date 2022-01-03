#pragma once

#include "rws/core/chunk.h"
#include "rws/core/chunk_string.h"
#include "rws/core/core_common.h"

namespace Rws {

    class TextureStruct;

    class Texture : public Chunk
    {
        RWS_CHUNK(Texture, ID_TEXTURE, ID_NAOBJECT, RWS_TRUE)

    public:
        TextureStruct* GetStruct() const { return GetChild<TextureStruct>(); }
        String* GetTextureName() const { return GetChild<String>(0); }
        String* GetMaskName() const { return GetChild<String>(1); }
    };

    class TextureStruct : public Chunk
    {
        RWS_CHUNK(TextureStruct, ID_STRUCT, ID_TEXTURE, RWS_FALSE)

    public:
        enum StreamFlags
        {
            STREAMFLAGS_NA = 0x0,
            STREAMFLAGS_USERMIPMAPS = 0x1
        };

        TextureFilterMode filtering;
        TextureAddressMode addressingU;
        TextureAddressMode addressingV;
        StreamFlags flags;

        Texture* GetTexture() const { return GetParentAs<Texture>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}