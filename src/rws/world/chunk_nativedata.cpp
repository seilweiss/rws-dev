#include "rws/world/chunk_nativedata.h"

#include "rws/world/native/nativedata_default.h"

#include <map>

namespace Rws {

    namespace {

        struct PlatformType
        {
            NativeData::PlatformConstructor constructor;
        };

        std::map<UInt32, PlatformType> s_platformTypes;

    }

    void NativeData::RegisterPlatformType(UInt32 platformID, PlatformConstructor constructor)
    {
        s_platformTypes[platformID].constructor = constructor;
    }

    void NativeData::UnregisterPlatformType(UInt32 platformID)
    {
        if (s_platformTypes.find(platformID) != s_platformTypes.end())
        {
            s_platformTypes.erase(platformID);
        }
    }

    void NativeData::ClearPlatformTypes()
    {
        s_platformTypes.clear();
    }

    NativeDataPlatform* NativeData::CreatePlatformData(UInt32 platformID)
    {
        NativeDataPlatform* platform = RWS_NULL;

        if (platformID != ID_NAPLATFORM && s_platformTypes.find(platformID) != s_platformTypes.end())
        {
            platform = s_platformTypes[platformID].constructor();
        }

        if (!platform)
        {
            platform = new NativeDataDefault();
        }

        return platform;
    }

    NativeDataStruct::~NativeDataStruct()
    {
        if (m_platform)
        {
            delete m_platform;
        }
    }

    void NativeDataStruct::CreatePlatformData()
    {
        m_platform = NativeData::CreatePlatformData(platformID);
    }

    void NativeDataStruct::Read(Stream* stream, UInt32 length)
    {
        NativeData* nativeData = GetNativeData();

        if (!nativeData)
        {
            return;
        }

        UInt32 start = stream->Tell();

        stream->Read(&platformID);

        UInt32 dataLength = length - (stream->Tell() - start);

        CreatePlatformData();

        if (m_platform)
        {
            m_platform->Read(stream, dataLength, nativeData);
        }
    }

    void NativeDataStruct::Write(Stream* stream)
    {
        NativeData* nativeData = GetNativeData();

        if (!nativeData)
        {
            return;
        }

        stream->Write(&platformID);

        if (m_platform)
        {
            m_platform->Write(stream, nativeData);
        }
    }

}