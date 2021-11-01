#include "rws/world/chunk_materiallist.h"

namespace Rws {

    void MaterialListStruct::Read(Stream* stream, UInt32 length)
    {
        Int32 len;
        stream->Read(&len);

        matindex.reserve(len);

        for (Int32 i = 0; i < len; i++)
        {
            Int32 index;
            stream->Read(&index);
            matindex.push_back(index);
        }
    }

    void MaterialListStruct::Write(Stream* stream)
    {
        Int32 len = (Int32)matindex.size();
        stream->Write(&len);

        for (Int32 i = 0; i < len; i++)
        {
            stream->Write(&matindex[i]);
        }
    }

}