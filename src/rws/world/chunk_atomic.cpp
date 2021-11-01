#include "rws/world/chunk_atomic.h"

namespace Rws {

    void AtomicStruct::Read(Stream* stream, UInt32 length)
    {
        stream->Read(&frameIndex);
        stream->Read(&geomIndex);
        stream->Read(&flags);
        stream->Read(&unused);
    }

    void AtomicStruct::Write(Stream* stream)
    {
        stream->Write(&frameIndex);
        stream->Write(&geomIndex);
        stream->Write(&flags);
        stream->Write(&unused);
    }

}