#pragma once

#include "rws/core/native/texturenative_xbox.h"
#include "rws/world/native/nativedata_xbox.h"

namespace Rws {

    namespace Xbox {

        inline void Register()
        {
            TextureNativeXbox::Register();
            NativeDataXbox::Register();
        }

        inline void Unregister()
        {
            TextureNativeXbox::Unregister();
            NativeDataXbox::Unregister();
        }

    }

}