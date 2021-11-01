#pragma once

#include "rws/core/chunk.h"
#include "rws/core/core_common.h"

#include <vector>
#include <array>

namespace Rws {

    class Skin : public Chunk
    {
        RWS_CHUNK(Skin, ID_SKINPLUGIN, ID_NAOBJECT, RWS_FALSE)

    public:
        UInt8 maxVertexWeights;
        std::vector<UInt8> usedBones;
        std::vector<std::array<UInt8, 4>> matrixIndices;
        std::vector<std::array<Real, 4>> matrixWeights;
        std::vector<Matrix> invBoneToSkinMats;

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}