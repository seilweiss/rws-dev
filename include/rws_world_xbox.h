#pragma once

#include "rws/world/native/nativedata_xbox.h"

namespace Rws {

    namespace WorldPlugin {

        inline void RegisterXbox()
        {
            NativeDataXbox::Register();
        }

        inline void UnregisterXbox()
        {
            NativeDataXbox::Unregister();
        }

    }

}