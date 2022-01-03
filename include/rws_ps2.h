#pragma once

#include "rws/world/native/nativedata_ps2.h"

namespace Rws {

    namespace PS2 {

        inline void Register()
        {
            NativeDataPS2::Register();
        }

        inline void Unregister()
        {
            NativeDataPS2::Unregister();
        }

    }

}