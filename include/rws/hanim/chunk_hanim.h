#pragma once

#include "rws/core/chunk.h"

#include <vector>

namespace Rws {

    class HAnimHierarchy : public Chunk
    {
        RWS_CHUNK(HAnimHierarchy, ID_HANIMPLUGIN, ID_NAOBJECT, RWS_FALSE)

    public:
        struct NodeInfo
        {
            Int32 nodeID;
            Int32 nodeIndex;
            Int32 flags;
        };

        enum Flags
        {
            SUBHIERARCHY = 0x1,
            NOMATRICES = 0x2,
            UPDATEMODELLINGMATRICES = 0x1000,
            UPDATELTMS = 0x2000,
            LOCALSPACEMATRICES = 0x4000
        };

        enum NodeInfoFlags
        {
            POPPARENTMATRIX = 0x1,
            PUSHPARENTMATRIX = 0x2
        };

        Int32 version;
        Int32 nodeID;
        Int32 flags;
        Int32 keyFrameSize;

        std::vector<NodeInfo> nodes;

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}