#pragma once

#include "rws/core/core_common.h"

#include <vector>

namespace Rws {

    struct Triangle
    {
        UInt16 vertIndex[3];
        UInt16 matIndex;
    };

    struct MorphTarget
    {
        Sphere boundingSphere;
        std::vector<V3d> verts;
        std::vector<V3d> normals;
    };

}