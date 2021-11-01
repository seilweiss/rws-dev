#pragma once

#include "rws/core/chunk.h"
#include "rws/world/chunk_material.h"

#include <vector>

namespace Rws {

    class MaterialListStruct;

    class MaterialList : public Chunk
    {
        RWS_CHUNK(MaterialList, ID_MATLIST, ID_NAOBJECT, RWS_TRUE)

    public:
        MaterialListStruct* GetStruct() const { return GetChild<MaterialListStruct>(); }
        Material* GetMaterial(Int32 index) const { return GetChild<Material>(index); }
        std::vector<Material*> GetMaterials() const { return GetChildren<Material>(); }
        UInt32 GetMaterialCount() const { return GetChildCount<Material>(); }
    };

    class MaterialListStruct : public Chunk
    {
        RWS_CHUNK(MaterialListStruct, ID_STRUCT, ID_MATLIST, RWS_FALSE)

    public:
        std::vector<Int32> matindex;

        MaterialList* GetMaterialList() const { return GetParentAs<MaterialList>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}