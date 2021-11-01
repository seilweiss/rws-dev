#include "rws/skin/chunk_skin.h"

#include "rws/core/chunk_extension.h"
#include "rws/world/chunk_geometry.h"

namespace Rws {

    void Skin::Read(Stream* stream, UInt32 length)
    {
        Geometry* geometry = GetExtensionParentAs<Geometry>();

        if (!geometry)
        {
            return;
        }

        GeometryStruct* geomStruct = geometry->GetStruct();

        if (!geomStruct)
        {
            return;
        }

        UInt8 numBones, numUsedBones, pad;

        stream->Read(&numBones);
        stream->Read(&numUsedBones);
        stream->Read(&maxVertexWeights);
        stream->Read(&pad);

        usedBones.reserve(numUsedBones);

        for (UInt8 i = 0; i < numUsedBones; i++)
        {
            UInt8 index;
            stream->Read(&index);
            usedBones.push_back(index);
        }

        matrixIndices.reserve(geomStruct->numVertices);

        for (Int32 i = 0; i < geomStruct->numVertices; i++)
        {
            std::array<UInt8, 4> indices;

            for (UInt32 j = 0; j < 4; j++)
            {
                UInt8 index;
                stream->Read(&index);
                indices[j] = index;
            }

            matrixIndices.push_back(indices);
        }

        invBoneToSkinMats.reserve(numBones);

        for (UInt8 i = 0; i < numBones; i++)
        {
            Matrix m;
            m.Read(stream);
            invBoneToSkinMats.push_back(m);
        }

        // todo: read skin splits
    }

    void Skin::Write(Stream* stream)
    {
        // todo
    }

}