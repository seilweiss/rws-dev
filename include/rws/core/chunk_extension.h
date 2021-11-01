#pragma once

#include "rws/core/chunk.h"

namespace Rws {

    class Extension : public Chunk
    {
        RWS_CHUNK(Extension, ID_EXTENSION, ID_NAOBJECT, RWS_TRUE)
    };

}