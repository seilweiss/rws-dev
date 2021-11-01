#pragma once

#include "rws/skin/chunk_skin.h"

namespace Rws {

    namespace SkinPlugin {

        inline void Register()
        {
            Skin::Register();
        }

        inline void Unregister()
        {
            Skin::Unregister();
        }

    }

}