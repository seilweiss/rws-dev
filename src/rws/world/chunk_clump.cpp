#include "rws/world/chunk_clump.h"

namespace Rws {

    namespace {

        struct ClumpHeader
        {
            Int32 numAtomics;
            Int32 numLights;
            Int32 numCameras;

            void Read(Stream* stream)
            {
                stream->Read32(this, sizeof(*this));
            }

            void Write(Stream* stream)
            {
                stream->Write32(this, sizeof(*this));
            }
        };

    }

    void ClumpStruct::Read(Stream* stream, UInt32 length)
    {
        ClumpHeader header;
        header.Read(stream);
    }

    void ClumpStruct::Write(Stream* stream)
    {
        ClumpHeader header = { 0, 0, 0 };
        Clump* clump = GetClump();

        if (clump)
        {
            header.numAtomics = clump->GetAtomicCount();
            header.numLights = clump->GetLightCount();
            header.numCameras = clump->GetCameraCount();
        }

        header.Write(stream);
    }

}