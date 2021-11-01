#pragma once

#include "rws/core/chunk.h"
#include "rws/core/chunk_string.h"

namespace Rws {

    class TextureStruct;

    class Texture : public Chunk
    {
        RWS_CHUNK(Texture, ID_TEXTURE, ID_NAOBJECT, RWS_TRUE)

    public:
        TextureStruct* GetStruct() const { return GetChild<TextureStruct>(); }
        String* GetName() const { return GetChild<String>(0); }
        String* GetMaskName() const { return GetChild<String>(1); }
    };

    class TextureStruct : public Chunk
    {
        RWS_CHUNK(TextureStruct, ID_STRUCT, ID_TEXTURE, RWS_FALSE)

    public:
        enum FilterMode
        {
            FILTER_NA = 0,
            FILTER_NEAREST = 1,
            FILTER_LINEAR = 2,
            FILTER_MIPNEAREST = 3,
            FILTER_MIPLINEAR = 4,
            FILTER_LINEARMIPNEAREST = 5,
            FILTER_LINEARMIPLINEAR = 6,
            FILTER_MASK = 0xFF
        };

        enum AddressMode
        {
            ADDRESS_NA = 0,
            ADDRESS_WRAP = 1,
            ADDRESS_MIRROR = 2,
            ADDRESS_CLAMP = 3,
            ADDRESS_BORDER = 4,
            ADDRESS_UMASK = 0xF00,
            ADDRESS_VMASK = 0xF000,
            ADDRESS_MASK = (ADDRESS_UMASK | ADDRESS_VMASK)
        };

        enum StreamFlags
        {
            STREAMFLAGS_NA = 0x0,
            STREAMFLAGS_USERMIPMAPS = 0x1
        };

        FilterMode filtering;
        AddressMode addressingU;
        AddressMode addressingV;
        StreamFlags flags;

        Texture* GetTexture() const { return GetParentAs<Texture>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}