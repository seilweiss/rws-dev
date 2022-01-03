#include "rws/core/chunk_texturenative.h"

#include "rws/core/native/texturenative_default.h"

#include <map>

namespace Rws {

    namespace {

        struct PlatformType
        {
            UInt32 magic;
            TextureNative::PlatformConstructor constructor;
        };

        std::map<UInt32, PlatformType> s_platformTypes;

    }

    void TextureNative::RegisterPlatformType(UInt32 platformID, UInt32 magic, PlatformConstructor constructor)
    {
        s_platformTypes[platformID].magic = magic;
        s_platformTypes[platformID].constructor = constructor;
    }

    void TextureNative::UnregisterPlatformType(UInt32 platformID)
    {
        if (s_platformTypes.find(platformID) != s_platformTypes.end())
        {
            s_platformTypes.erase(platformID);
        }
    }

    void TextureNative::ClearPlatformTypes()
    {
        s_platformTypes.clear();
    }

    TextureNativePlatform* TextureNative::CreatePlatformData(UInt32 platformID)
    {
        TextureNativePlatform* platform = RWS_NULL;

        if (platformID != ID_NAPLATFORM && s_platformTypes.find(platformID) != s_platformTypes.end())
        {
            platform = s_platformTypes[platformID].constructor();
        }

        if (!platform)
        {
            platform = new TextureNativeDefault();
        }

        return platform;
    }

    TextureNativeStruct::~TextureNativeStruct()
    {
        if (m_platform)
        {
            delete m_platform;
        }
    }

    void TextureNativeStruct::CreatePlatformData()
    {
        m_platform = TextureNative::CreatePlatformData(platformID);
    }

    void TextureNativeStruct::Read(Stream* stream, UInt32 length)
    {
        TextureNative* textureNative = GetTextureNative();

        if (!textureNative)
        {
            return;
        }

        UInt32 start = stream->Tell();
        UInt32 magic;

        stream->Read(&magic);

        UInt32 dataLength = length - (stream->Tell() - start);

        platformID = ID_NAPLATFORM;

        for (auto it : s_platformTypes)
        {
            if (it.second.magic == magic)
            {
                platformID = it.first;
                break;
            }
        }

        CreatePlatformData();

        if (m_platform)
        {
            m_platform->Read(stream, dataLength, textureNative);
        }
    }

    void TextureNativeStruct::Write(Stream* stream)
    {
        TextureNative* textureNative = GetTextureNative();

        if (!textureNative)
        {
            return;
        }

        UInt32 magic = 0;

        if (platformID != ID_NAPLATFORM && s_platformTypes.find(platformID) != s_platformTypes.end())
        {
            magic = s_platformTypes[platformID].magic;
        }

        stream->Write(&magic);

        if (m_platform)
        {
            m_platform->Write(stream, textureNative);
        }
    }

}