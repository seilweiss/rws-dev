#pragma once

#include "rws/hanim/chunk_hanim.h"

namespace Rws {

    namespace HAnimPlugin {

        inline void Register()
        {
            HAnimHierarchy::Register();
        }

        inline void Unregister()
        {
            HAnimHierarchy::Unregister();
        }

    }

}