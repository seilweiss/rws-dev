#pragma once

#include "rws/core/chunk.h"
#include "rws/core/core_common.h"
#include "rws/world/world_common.h"
#include "rws/world/chunk_materiallist.h"

#include <vector>

namespace Rws {

    class GeometryStruct;

    class Geometry : public Chunk
    {
        RWS_CHUNK(Geometry, ID_GEOMETRY, ID_NAOBJECT, RWS_TRUE)

    public:
        GeometryStruct* GetStruct() const { return GetChild<GeometryStruct>(); }
        MaterialList* GetMaterialList() const { return GetChild<MaterialList>(); }
    };

    class GeometryStruct : public Chunk
    {
        RWS_CHUNK(GeometryStruct, ID_STRUCT, ID_GEOMETRY, RWS_FALSE)

    public:
        enum Flags
        {
            TRISTRIP = 0x1,
            POSITIONS = 0x2,
            TEXTURED = 0x4,
            PRELIT = 0x8,
            NORMALS = 0x10,
            LIGHT = 0x20,
            MODULATEMATERIALCOLOR = 0x40,
            TEXTURED2 = 0x80,
            NATIVE = 0x01000000,
            NATIVEINSTANCE = 0x02000000,
            FLAGSMASK = 0xFF,
            NATIVEFLAGSMASK = 0x0F000000,
            NUMTEXCOORDSMASK = 0xFF0000
        };

        Int32 format;
        Int32 numVertices;
        std::vector<Triangle> triangles;
        std::vector<RGBA> preLitLum;
        std::vector<TexCoords> texCoords[8];
        std::vector<MorphTarget> morphTargets;

        Bool IsTriStrip() const { return format & TRISTRIP; }
        Bool HasPositions() const { return format & POSITIONS; }
        Bool HasColors() const { return format & PRELIT; }
        Bool HasNormals() const { return format & NORMALS; }
        Bool IsLit() const { return format & LIGHT; }
        Bool ModulatesMaterialColor() const { return format & MODULATEMATERIALCOLOR; }
        Bool IsNative() const { return format & NATIVE; }
        Bool IsNativeInstance() const { return format & NATIVEINSTANCE; }

        Int32 GetNumTexCoordSets() const
        {
            if (format & NUMTEXCOORDSMASK)
            {
                return (format & NUMTEXCOORDSMASK) >> 16;
            }

            if (format & TEXTURED2)
            {
                return 2;
            }

            if (format & TEXTURED)
            {
                return 1;
            }

            return 0;
        }

        Geometry* GetGeometry() const { return GetParentAs<Geometry>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}