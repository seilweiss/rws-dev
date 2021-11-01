#pragma once

#include "rws/world/native/nativedata_gc.h"

namespace Rws {

    namespace WorldPlugin {

        inline void RegisterGameCube()
        {
            NativeDataGameCube::Register();
        }

        inline void UnregisterGameCube()
        {
            NativeDataGameCube::Unregister();
        }

    }

}