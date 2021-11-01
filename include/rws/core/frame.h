#pragma once

#include "rws/core/core_common.h"

namespace Rws {

    struct Frame
    {
        V3d right, up, at, pos;
        Int32 parentIndex;
        UInt32 data;

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