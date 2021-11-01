#pragma once

#include "rws/core/chunk.h"

namespace Rws {

    class NativeDataPlatform;
    class NativeDataStruct;

    class NativeData : public Chunk
    {
        RWS_CHUNK(NativeData, ID_NATIVEDATAPLUGIN, ID_NAOBJECT, RWS_TRUE)

    public:
        typedef NativeDataPlatform* (*PlatformConstructor)();

        static void RegisterPlatformType(UInt32 platformID, PlatformConstructor constructor);
        static void UnregisterPlatformType(UInt32 platformID);
        static void ClearPlatformTypes();
        static NativeDataPlatform* CreatePlatformData(UInt32 platformID);

        NativeDataStruct* GetStruct() const { return GetChild<NativeDataStruct>(); }
    };

    class NativeDataStruct : public Chunk
    {
        RWS_CHUNK(NativeDataStruct, ID_STRUCT, ID_NATIVEDATAPLUGIN, RWS_FALSE)

    public:
        UInt32 platformID = ID_NAPLATFORM;

        ~NativeDataStruct();

        NativeData* GetNativeData() const { return GetParentAs<NativeData>(); }

        NativeDataPlatform* GetPlatformData() const { return m_platform; }
        void CreatePlatformData();

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream);

    private:
        NativeDataPlatform* m_platform = RWS_NULL;
    };

}