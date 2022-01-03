#pragma once

#include "rws/world/native/nativedata_gc.h"

namespace Rws {

    namespace GameCube {

        inline void Register()
        {
            NativeDataGameCube::Register();
        }

        inline void Unregister()
        {
            NativeDataGameCube::Unregister();
        }

    }

}