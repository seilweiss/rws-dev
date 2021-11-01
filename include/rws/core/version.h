#pragma once

#include "rws/core/types.h"

namespace Rws {

    extern UInt32 __defaultVersion;
    extern UInt32 __defaultBuildNum;

    inline UInt32 GetDefaultVersion() { return __defaultVersion; }
    inline UInt32 GetDefaultBuildNum() { return __defaultBuildNum; }
    inline void SetDefaultVersion(UInt32 version) { __defaultVersion = version; }
    inline void SetDefaultBuildNum(UInt32 buildNum) { __defaultBuildNum = buildNum; }

    inline UInt32 MakeLibraryID(UInt32 version, UInt32 buildNum)
    {
        return (((version - 0x30000) & 0x3FF00) << 14) | ((version & 0x3F) << 16) | (buildNum & 0xFFFF);
    }

    inline UInt32 LibraryIDToVersion(UInt32 libraryID)
    {
        return (((libraryID >> 14) & 0x3FF00) + 0x30000) | ((libraryID >> 16) & 0xFFFF);
    }

    inline UInt32 LibraryIDToBuildNum(UInt32 libraryID)
    {
        return libraryID & 0xFFFF;
    }

}