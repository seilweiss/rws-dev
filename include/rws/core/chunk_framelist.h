#pragma once

#include "rws/core/chunk.h"
#include "rws/core/frame.h"

#include <vector>

namespace Rws {

    class FrameListStruct;

    class FrameList : public Chunk
    {
        RWS_CHUNK(FrameList, ID_FRAMELIST, ID_NAOBJECT, RWS_TRUE)

    public:
        FrameListStruct* GetStruct() const { return GetChild<FrameListStruct>(); }
    };

    class FrameListStruct : public Chunk
    {
        RWS_CHUNK(FrameListStruct, ID_STRUCT, ID_FRAMELIST, RWS_FALSE)

    public:
        std::vector<Frame> frames;

        FrameList* GetFrameList() const { return GetParentAs<FrameList>(); }

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}