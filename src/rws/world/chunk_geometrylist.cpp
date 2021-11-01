#include "rws/world/chunk_geometrylist.h"

namespace Rws {

    void GeometryListStruct::Read(Stream* stream, UInt32 length)
    {
        Int32 numGeoms;
        stream->Read(&numGeoms);
    }

    void GeometryListStruct::Write(Stream* stream)
    {
        Int32 numGeoms = 0;
        GeometryList* geomList = GetGeometryList();

        if (geomList)
        {
            numGeoms = geomList->GetGeometryCount();
        }

        stream->Write(&numGeoms);
    }

}