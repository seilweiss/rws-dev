#pragma once

#include "rws/core/types.h"
#include "rws/core/mem.h"

#include <cstdio>

namespace Rws {

    struct ChunkHeader
    {
        UInt32 type;
        UInt32 length;
        UInt32 libraryID;
    };

    class Chunk;

    class Stream
    {
    public:
        enum Type
        {
            TYPE_NA,
            TYPE_FILE,
            TYPE_MEMORY,
            TYPE_CUSTOM
        };

        enum AccessType
        {
            ACCESS_NA,
            ACCESS_READ,
            ACCESS_WRITE,
            ACCESS_APPEND
        };

        struct CustomData
        {
            void* userdata;
            Bool(*open)(AccessType accessType, void* userdata);
            Bool(*close)(void* userdata);
            Bool(*seek)(UInt32 position, void* userdata);
            UInt32(*read)(void* buffer, UInt32 length, void* userdata);
            UInt32(*write)(const void* buffer, UInt32 length, void* userdata);
        };

        typedef Chunk* (*ChunkConstructor)();

        static void RegisterChunkType(UInt32 type, UInt32 parentType, ChunkConstructor constructor);
        static void UnregisterChunkType(UInt32 type, UInt32 parentType);
        static void ClearChunkTypes();

        Stream() {}
        Stream(FILE* file, AccessType accessType = ACCESS_READ) { Open(file, accessType); }
        Stream(const Char* filename, AccessType accessType = ACCESS_READ) { Open(filename, accessType); }
        Stream(UInt8* memory, UInt32 length, AccessType accessType = ACCESS_READ) { Open(memory, length, accessType); }
        Stream(CustomData* custom, AccessType accessType = ACCESS_READ) { Open(custom, accessType); }
        ~Stream() { Close(); }

        Bool IsOpen() const { return m_type != TYPE_NA; }

        Endian GetEndian() const { return m_endian; }
        void SetEndian(Endian endian) { m_endian = endian; }

        Bool Open(FILE* file, AccessType accessType = ACCESS_READ);
        Bool Open(const Char* filename, AccessType accessType = ACCESS_READ);
        Bool Open(UInt8* memory, UInt32 length, AccessType accessType = ACCESS_READ);
        Bool Open(CustomData* custom, AccessType accessType = ACCESS_READ);
        Bool Close();

        Bool Seek(UInt32 position);
        Bool Skip(UInt32 offset) { return Seek(m_position + offset); }
        UInt32 Tell() const { return m_position; }

        UInt32 Read(void* buffer, UInt32 length);
        UInt32 Write(const void* buffer, UInt32 length);

        Bool Read(Int8* ints, UInt32 numBytes = sizeof(Int8)) { return Read8((void*)ints, numBytes); }
        Bool Read(UInt8* ints, UInt32 numBytes = sizeof(UInt8)) { return Read8((void*)ints, numBytes); }
        Bool Read(Int16* ints, UInt32 numBytes = sizeof(Int16)) { return Read16((void*)ints, numBytes); }
        Bool Read(UInt16* ints, UInt32 numBytes = sizeof(UInt16)) { return Read16((void*)ints, numBytes); }
        Bool Read(Int32* ints, UInt32 numBytes = sizeof(Int32)) { return Read32((void*)ints, numBytes); }
        Bool Read(UInt32* ints, UInt32 numBytes = sizeof(UInt32)) { return Read32((void*)ints, numBytes); }
        Bool Read(Real* reals, UInt32 numBytes = sizeof(Real)) { return Read32((void*)reals, numBytes); }

        Bool Write(const Int8* ints, UInt32 numBytes = sizeof(Int8)) { return Write8((const void*)ints, numBytes); }
        Bool Write(const UInt8* ints, UInt32 numBytes = sizeof(UInt8)) { return Write8((const void*)ints, numBytes); }
        Bool Write(const Int16* ints, UInt32 numBytes = sizeof(Int16)) { return Write16((const void*)ints, numBytes); }
        Bool Write(const UInt16* ints, UInt32 numBytes = sizeof(UInt16)) { return Write16((const void*)ints, numBytes); }
        Bool Write(const Int32* ints, UInt32 numBytes = sizeof(Int32)) { return Write32((const void*)ints, numBytes); }
        Bool Write(const UInt32* ints, UInt32 numBytes = sizeof(UInt32)) { return Write32((const void*)ints, numBytes); }
        Bool Write(const Real* reals, UInt32 numBytes = sizeof(Real)) { return Write32((const void*)reals, numBytes); }

        Bool Read8(void* buffer, UInt32 numBytes);
        Bool Read16(void* buffer, UInt32 numBytes);
        Bool Read32(void* buffer, UInt32 numBytes);
        Bool Write8(const void* buffer, UInt32 numBytes);
        Bool Write16(const void* buffer, UInt32 numBytes);
        Bool Write32(const void* buffer, UInt32 numBytes);

        Bool ReadChunkHeader(ChunkHeader* header);
        Bool WriteChunkHeader(ChunkHeader* header);

        Chunk* ReadChunk(Chunk* parent = RWS_NULL);
        Bool WriteChunk(Chunk* chunk);

    private:
        struct FileData
        {
            FILE* fp;
        };

        struct MemoryData
        {
            UInt8* start;
            UInt32 length;
        };

        struct DataUnion
        {
            FileData file;
            MemoryData memory;
            CustomData custom;
        };

        Type m_type = TYPE_NA;
        AccessType m_accessType = ACCESS_NA;
        Endian m_endian = LITTLE_ENDIAN;
        UInt32 m_position = 0;
        DataUnion m_data = {};
    };

}