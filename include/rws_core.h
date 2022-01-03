#pragma once

#include "rws/core/types.h"
#include "rws/core/version.h"
#include "rws/core/mem.h"
#include "rws/core/stream.h"
#include "rws/core/chunk.h"
#include "rws/core/ids.h"
#include "rws/core/core_common.h"

#include "rws/core/chunk_default.h"
#include "rws/core/chunk_extension.h"
#include "rws/core/chunk_framelist.h"
#include "rws/core/chunk_string.h"
#include "rws/core/chunk_texture.h"
#include "rws/core/chunk_texdictionary.h"
#include "rws/core/chunk_texturenative.h"
#include "rws/core/chunk_unicodestring.h"

namespace Rws {

    namespace Core {

        inline void Register()
        {
            Extension::Register();
            FrameList::Register();
            FrameListStruct::Register();
            String::Register();
            Texture::Register();
            TextureStruct::Register();
            TexDictionary::Register();
            TexDictionaryStruct::Register();
            TextureNative::Register();
            TextureNativeStruct::Register();
            UnicodeString::Register();
        }

        inline void Unregister()
        {
            Extension::Unregister();
            FrameList::Unregister();
            FrameListStruct::Unregister();
            String::Unregister();
            Texture::Unregister();
            TextureStruct::Unregister();
            TexDictionary::Unregister();
            TexDictionaryStruct::Unregister();
            TextureNative::Unregister();
            TextureNativeStruct::Unregister();
            UnicodeString::Unregister();
        }

    }

}