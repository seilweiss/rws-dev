#pragma once

#include "rws/core/stream.h"
#include "rws/world/chunk_nativedata.h"

#define RWS_NATIVEDATAPLATFORM(ClassName, platformID)\
    public:\
        static void Register() { Rws::NativeData::RegisterPlatformType((platformID), [] { return (NativeDataPlatform*)new ClassName; }); }\
        static void Unregister() { Rws::NativeData::UnregisterPlatformType((platformID)); }\
        static const char* GetNameStatic() { return #ClassName; }\
        static UInt32 GetPlatformIDStatic() { return (platformID); }\
        virtual const char* GetName() const { return #ClassName; }\
        virtual UInt32 GetPlatformID() const { return (platformID); }

namespace Rws {

    class NativeDataPlatform
    {
        RWS_NATIVEDATAPLATFORM(NativeDataPlatform, ID_NAPLATFORM)

    public:
        virtual void Read(Stream* stream, UInt32 length, NativeData* nativeData) {}
        virtual void Write(Stream* stream, NativeData* nativeData) {}
    };

}