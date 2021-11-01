#include "rws/world/chunk_geometry.h"

namespace Rws {

    void GeometryStruct::Read(Stream* stream, UInt32 length)
    {
        Int32 numTriangles, numMorphTargets;

        stream->Read(&format);
        stream->Read(&numTriangles);
        stream->Read(&numVertices);
        stream->Read(&numMorphTargets);

        if (!IsNative() && numVertices)
        {
            if (HasColors())
            {
                preLitLum.reserve(numVertices);

                for (Int32 i = 0; i < numVertices; i++)
                {
                    RGBA rgba;
                    rgba.Read(stream);
                    preLitLum.push_back(rgba);
                }
            }

            Int32 numTexCoordSets = GetNumTexCoordSets();

            for (Int32 i = 0; i < numTexCoordSets; i++)
            {
                texCoords[i].reserve(numVertices);

                for (Int32 j = 0; j < numVertices; j++)
                {
                    TexCoords tc;
                    tc.Read(stream);
                    texCoords[i].push_back(tc);
                }
            }

            triangles.reserve(numTriangles);

            for (Int32 i = 0; i < numTriangles; i++)
            {
                UInt32 vertex01, vertex2Mat;
                stream->Read(&vertex01);
                stream->Read(&vertex2Mat);

                Triangle tri;
                tri.vertIndex[0] = (vertex01 >> 16) & 0xffff;
                tri.vertIndex[1] = (vertex01) & 0xffff;
                tri.vertIndex[2] = (vertex2Mat >> 16) & 0xffff;
                tri.matIndex = (vertex2Mat) & 0xffff;

                triangles.push_back(tri);
            }
        }

        morphTargets.reserve(numMorphTargets);

        for (Int32 i = 0; i < numMorphTargets; i++)
        {
            MorphTarget mt;
            Bool pointsPresent, normalsPresent;

            mt.boundingSphere.Read(stream);
            stream->Read(&pointsPresent);
            stream->Read(&normalsPresent);

            if (pointsPresent)
            {
                mt.verts.reserve(numVertices);

                for (Int32 j = 0; j < numVertices; j++)
                {
                    V3d v;
                    v.Read(stream);
                    mt.verts.push_back(v);
                }
            }

            if (normalsPresent)
            {
                mt.normals.reserve(numVertices);

                for (Int32 j = 0; j < numVertices; j++)
                {
                    V3d n;
                    n.Read(stream);
                    mt.normals.push_back(n);
                }
            }

            morphTargets.push_back(mt);
        }
    }

    void GeometryStruct::Write(Stream* stream)
    {
        Int32 numTriangles = (Int32)triangles.size();
        Int32 numMorphTargets = (Int32)morphTargets.size();

        stream->Write(&format);
        stream->Write(&numTriangles);
        stream->Write(&numVertices);
        stream->Write(&numMorphTargets);

        if (!IsNative() && numVertices)
        {
            if (HasColors())
            {
                for (Int32 i = 0; i < numVertices; i++)
                {
                    preLitLum[i].Write(stream);
                }
            }

            Int32 numTexCoordSets = GetNumTexCoordSets();

            for (Int32 i = 0; i < numTexCoordSets; i++)
            {
                for (Int32 j = 0; j < numVertices; j++)
                {
                    texCoords[i][j].Write(stream);
                }
            }

            for (Int32 i = 0; i < numTriangles; i++)
            {
                Triangle& tri = triangles[i];

                UInt32 vertex01 = (tri.vertIndex[0] << 16) | tri.vertIndex[1];
                UInt32 vertex2Mat = (tri.vertIndex[2] << 16) | tri.matIndex;

                stream->Write(&vertex01);
                stream->Write(&vertex2Mat);
            }
        }

        for (Int32 i = 0; i < numMorphTargets; i++)
        {
            MorphTarget& mt = morphTargets[i];

            mt.boundingSphere.Write(stream);

            Bool pointsPresent = (mt.verts.size() > 0);
            Bool normalsPresent = (mt.normals.size() > 0);

            stream->Write(&pointsPresent);
            stream->Write(&normalsPresent);

            if (pointsPresent)
            {
                for (Int32 j = 0; j < numVertices; j++)
                {
                    mt.verts[j].Write(stream);
                }
            }

            if (normalsPresent)
            {
                for (Int32 j = 0; j < numVertices; j++)
                {
                    mt.normals[j].Write(stream);
                }
            }
        }
    }

}