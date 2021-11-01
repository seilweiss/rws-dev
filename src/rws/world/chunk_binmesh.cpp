#include "rws/world/chunk_binmesh.h"

namespace Rws {

    UInt32 BinMesh::CountIndices() const
    {
        UInt32 total = 0;

        for (const Mesh& m : meshes)
        {
            total += (UInt32)m.indices.size();
        }

        return total;
    }

    void BinMesh::Read(Stream* stream, UInt32 length)
    {
        UInt32 numMeshes, totalIndicesInMesh;

        stream->Read(&flags);
        stream->Read(&numMeshes);
        stream->Read(&totalIndicesInMesh);

        meshes.reserve(numMeshes);

        for (UInt32 i = 0; i < numMeshes; i++)
        {
            Mesh m;
            UInt32 numIndices;

            stream->Read(&numIndices);
            stream->Read(&m.matIndex);

            m.indices.reserve(numIndices);

            for (UInt32 j = 0; j < numIndices; j++)
            {
                Int32 index;
                stream->Read(&index);
                m.indices.push_back(index);
            }

            meshes.push_back(m);
        }
    }

    void BinMesh::Write(Stream* stream)
    {
        UInt32 numMeshes = (UInt32)meshes.size();
        UInt32 totalIndicesInMesh = CountIndices();

        stream->Write(&flags);
        stream->Write(&numMeshes);
        stream->Write(&totalIndicesInMesh);

        for (Mesh& m : meshes)
        {
            UInt32 numIndices = (UInt32)m.indices.size();

            stream->Write(&numIndices);
            stream->Write(&m.matIndex);

            for (Int32 index : m.indices)
            {
                stream->Write(&index);
            }
        }
    }

}