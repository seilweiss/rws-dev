#pragma once

#include "rws/world/native/nativedata_ps2.h"

namespace Rws {

    namespace WorldPlugin {

        inline void RegisterPS2()
        {
            NativeDataPS2::Register();
        }

        inline void UnregisterPS2()
        {
            NativeDataPS2::Unregister();
        }

    }

}