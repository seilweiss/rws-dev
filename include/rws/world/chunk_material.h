#pragma once

#include "rws/core/chunk.h"
#include "rws/core/core_common.h"
#include "rws/core/chunk_texture.h"

namespace Rws {

    class MaterialStruct;

    class Material : public Chunk
    {
        RWS_CHUNK(Material, ID_MATERIAL, ID_NAOBJECT, RWS_TRUE)

    public:
        MaterialStruct* GetStruct() const { return GetChild<MaterialStruct>(); }
        Texture* GetTexture() const { return GetChild<Texture>(); }
    };

    class MaterialStruct : public Chunk
    {
        RWS_CHUNK(MaterialStruct, ID_STRUCT, ID_MATERIAL, RWS_FALSE)

    public:
        Int32 flags;
        RGBA color;
        Int32 unused;
        Bool textured;
        SurfaceProperties surfaceProps;

        Material* GetMaterial() const { return GetParentAs<Material>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}