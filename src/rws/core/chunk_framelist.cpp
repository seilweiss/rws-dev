#include "rws/core/chunk_framelist.h"

#include <algorithm>

namespace Rws {

    void FrameListStruct::Read(Stream* stream, UInt32 length)
    {
        Int32 numFrames;
        stream->Read(&numFrames);

        for (Int32 i = 0; i < numFrames; i++)
        {
            Frame frame;
            frame.Read(stream);

            frames.push_back(frame);
        }
    }

    void FrameListStruct::Write(Stream* stream)
    {
        Int32 numFrames = (Int32)frames.size();
        stream->Write(&numFrames);

        for (Frame& frame : frames)
        {
            frame.Write(stream);
        }
    }

}