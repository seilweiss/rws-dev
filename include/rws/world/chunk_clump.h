#pragma once

#include "rws/core/chunk.h"
#include "rws/core/chunk_framelist.h"
#include "rws/world/chunk_geometrylist.h"
#include "rws/world/chunk_atomic.h"

namespace Rws {

    class ClumpStruct;

    class Clump : public Chunk
    {
        RWS_CHUNK(Clump, ID_CLUMP, ID_NAOBJECT, RWS_TRUE)

    public:
        ClumpStruct* GetStruct() const { return GetChild<ClumpStruct>(); }
        FrameList* GetFrameList() const { return GetChild<FrameList>(); }
        GeometryList* GetGeometryList() const { return GetChild<GeometryList>(); }
        Atomic* GetAtomic(Int32 index) const { return GetChild<Atomic>(index); }
        std::vector<Atomic*> GetAtomics() const { return GetChildren<Atomic>(); }

        UInt32 GetAtomicCount() const { return GetChildCount<Atomic>(); }
        UInt32 GetLightCount() const { return GetChildCountByType(ID_LIGHT); }
        UInt32 GetCameraCount() const { return GetChildCountByType(ID_CAMERA); }
    };

    class ClumpStruct : public Chunk
    {
        RWS_CHUNK(ClumpStruct, ID_STRUCT, ID_CLUMP, RWS_FALSE)

    public:
        Clump* GetClump() const { return GetParentAs<Clump>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}