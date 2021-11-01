#include "rws/world/chunk_material.h"

namespace Rws {

    void MaterialStruct::Read(Stream* stream, UInt32 length)
    {
        stream->Read(&flags);
        color.Read(stream);
        stream->Read(&unused);
        stream->Read(&textured);
        surfaceProps.Read(stream);
    }

    void MaterialStruct::Write(Stream* stream)
    {
        stream->Write(&flags);
        color.Write(stream);
        stream->Write(&unused);
        stream->Write(&textured);
        surfaceProps.Write(stream);
    }

}