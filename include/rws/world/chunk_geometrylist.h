#pragma once

#include "rws/core/chunk.h"
#include "rws/world/chunk_geometry.h"

namespace Rws {

    class GeometryListStruct;

    class GeometryList : public Chunk
    {
        RWS_CHUNK(GeometryList, ID_GEOMETRYLIST, ID_NAOBJECT, RWS_TRUE)

    public:
        GeometryListStruct* GetStruct() const { return GetChild<GeometryListStruct>(); }
        Geometry* GetGeometry(Int32 index) const { return GetChild<Geometry>(index); }
        std::vector<Geometry*> GetGeometries() const { return GetChildren<Geometry>(); }
        UInt32 GetGeometryCount() const { return GetChildCount<Geometry>(); }
    };

    class GeometryListStruct : public Chunk
    {
        RWS_CHUNK(GeometryListStruct, ID_STRUCT, ID_GEOMETRYLIST, RWS_FALSE)

    public:
        GeometryList* GetGeometryList() const { return GetParentAs<GeometryList>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}