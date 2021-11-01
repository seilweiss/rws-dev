#pragma once

#include "rws/core/chunk.h"

#include <vector>

namespace Rws {

    class BinMesh : public Chunk
    {
        RWS_CHUNK(BinMesh, ID_BINMESHPLUGIN, ID_NAOBJECT, RWS_FALSE)

    public:
        struct Mesh
        {
            Int32 matIndex;
            std::vector<Int32> indices;
        };

        enum Flags
        {
            TRILIST = 0x0,
            TRISTRIP = 0x1,
            TRIFAN = 0x2,
            LINELIST = 0x4,
            POLYLINE = 0x8,
            POINTLIST = 0x10,
            PRIMMASK = 0xFF,
            UNINDEXED = 0x100
        };

        UInt32 flags;
        std::vector<Mesh> meshes;

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;

    private:
        UInt32 CountIndices() const;
    };

}