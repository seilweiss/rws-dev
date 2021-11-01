#include "rws/world/native/nativedata_gc.h"

#include "rws/world/chunk_geometry.h"

namespace Rws {

    namespace {

        struct VtxDescStream
        {
            UInt32 offset;
            UInt8 attr, stride, type, unknown;

            void Read(Stream* stream)
            {
                stream->Read(&offset);
                stream->Read(&attr);
                stream->Read(&stride);
                stream->Read(&type);
                stream->Read(&unknown);
            }

            void Write(Stream* stream)
            {
                stream->Write(&offset);
                stream->Write(&attr);
                stream->Write(&stride);
                stream->Write(&type);
                stream->Write(&unknown);
            }
        };

        struct IndexBufferStream
        {
            UInt32 offset;
            UInt32 size;

            void Read(Stream* stream)
            {
                stream->Read(&offset);
                stream->Read(&size);
            }

            void Write(Stream* stream)
            {
                stream->Write(&offset);
                stream->Write(&size);
            }
        };

    }

    void NativeDataGameCube::Read(Stream* stream, UInt32 length, NativeData* nativeData)
    {
        Geometry* geometry = nativeData->GetExtensionParentAs<Geometry>();

        if (!geometry)
        {
            return;
        }

        MaterialList* matList = geometry->GetMaterialList();

        if (!matList)
        {
            return;
        }

        UInt32 matCount = matList->GetMaterialCount();

        UInt32 headerSize, dataSize;

        stream->Read(&headerSize);
        stream->Read(&dataSize);

        Rws::Endian oldEndian = stream->GetEndian();

        stream->SetEndian(Rws::BIG_ENDIAN);

        UInt32 attrCount;

        stream->Read(&unknown1);
        stream->Read(&meshIndex);
        stream->Read(&unknown2);
        stream->Read(&attrCount);

        attributes.reserve(attrCount);

        for (UInt32 i = 0; i < attrCount; i++)
        {
            VtxDescStream descStream = {};
            descStream.Read(stream);

            GameCube::VertexDescriptor desc;
            desc.attr = (GameCube::GXAttr)descStream.attr;
            desc.stride = descStream.stride;
            desc.type = (GameCube::GXAttrType)descStream.type;
            desc.unknown = descStream.unknown;

            attributes.push_back(desc);
        }

        indexBuffers.reserve(matCount);

        for (UInt32 i = 0; i < matCount; i++)
        {
            IndexBufferStream bufferStream = {};
            bufferStream.Read(stream);

            GameCube::IndexBuffer buffer;

            indexBuffers.push_back(buffer);
        }

        UInt32 dataOffset = stream->Tell();

        for (UInt32 i = 0; i < matCount; i++)
        {

        }

        stream->SetEndian(oldEndian);
    }

    void NativeDataGameCube::Write(Stream* stream, NativeData* nativeData)
    {

    }

}