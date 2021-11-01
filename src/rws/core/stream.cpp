#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "rws/core/stream.h"

#include "rws/core/version.h"
#include "rws/core/chunk.h"
#include "rws/core/chunk_default.h"

#include <cstring>
#include <vector>
#include <map>

namespace Rws {

    namespace {

        struct ChunkType
        {
            std::map<UInt32, Stream::ChunkConstructor> constructors;
        };

        static std::map<UInt32, ChunkType> s_chunkTypes;

    }

    void Stream::RegisterChunkType(UInt32 type, UInt32 parentType, ChunkConstructor constructor)
    {
        s_chunkTypes[type].constructors[parentType] = constructor;
    }

    void Stream::UnregisterChunkType(UInt32 type, UInt32 parentType)
    {
        if (s_chunkTypes.find(type) != s_chunkTypes.end())
        {
            ChunkType& chunkType = s_chunkTypes[type];

            if (chunkType.constructors.find(parentType) != chunkType.constructors.end())
            {
                chunkType.constructors.erase(parentType);
            }
        }
    }

    void Stream::ClearChunkTypes()
    {
        s_chunkTypes.clear();
    }

    Bool Stream::Open(FILE* file, AccessType accessType)
    {
        if (accessType == ACCESS_NA)
        {
            return RWS_FALSE;
        }

        m_type = TYPE_FILE;
        m_accessType = accessType;
        m_position = ftell(file);
        m_data.file.fp = file;

        return RWS_TRUE;
    }

    Bool Stream::Open(const Char* filename, AccessType accessType)
    {
        if (accessType == ACCESS_NA)
        {
            return RWS_FALSE;
        }

        const char* mode = RWS_NULL;

        switch (accessType)
        {
        case ACCESS_READ:
            mode = "rb";
            break;
        case ACCESS_WRITE:
            mode = "wb";
            break;
        case ACCESS_APPEND:
            mode = "ab";
            break;
        }

        if (!mode)
        {
            return RWS_FALSE;
        }

        FILE* fp = fopen(filename, mode);

        if (!fp)
        {
            return RWS_FALSE;
        }

        m_type = TYPE_FILE;
        m_accessType = accessType;
        m_position = 0;
        m_data.file.fp = fp;

        return RWS_TRUE;
    }

    Bool Stream::Open(UInt8* memory, UInt32 length, AccessType accessType)
    {
        if (accessType == ACCESS_NA)
        {
            return RWS_FALSE;
        }

        if (accessType == ACCESS_APPEND) // currently unsupported
        {
            return RWS_FALSE;
        }

        m_type = TYPE_MEMORY;
        m_accessType = accessType;
        m_position = 0;
        m_data.memory.start = memory;
        m_data.memory.length = length;

        return RWS_TRUE;
    }

    Bool Stream::Open(CustomData* custom, AccessType accessType)
    {
        if (accessType == ACCESS_NA)
        {
            return RWS_FALSE;
        }

        if (!custom)
        {
            return RWS_FALSE;
        }

        if (!custom->open(accessType, custom->userdata))
        {
            return RWS_FALSE;
        }

        m_type = TYPE_CUSTOM;
        m_accessType = accessType;
        m_position = 0;
        m_data.custom = *custom;

        return RWS_TRUE;
    }

    Bool Stream::Close()
    {
        if (m_type == TYPE_NA)
        {
            return RWS_FALSE;
        }

        Bool success = RWS_FALSE;

        switch (m_type)
        {
        case TYPE_FILE:
        {
            if (fclose(m_data.file.fp) == 0)
            {
                m_data.file.fp = RWS_NULL;
                success = RWS_TRUE;
            }
            break;
        }
        case TYPE_MEMORY:
        {
            m_data.memory.start = RWS_NULL;
            m_data.memory.length = 0;
            success = RWS_TRUE;
            break;
        }
        case TYPE_CUSTOM:
        {
            success = m_data.custom.close(m_data.custom.userdata);
            break;
        }
        }

        m_type = TYPE_NA;
        m_accessType = ACCESS_NA;
        m_position = 0;

        return success;
    }

    Bool Stream::Seek(UInt32 position)
    {
        if (m_type == TYPE_NA)
        {
            return RWS_FALSE;
        }

        Bool success = RWS_FALSE;

        switch (m_type)
        {
        case TYPE_FILE:
        {
            if (fseek(m_data.file.fp, position, SEEK_SET) == 0)
            {
                success = RWS_TRUE;
            }
            break;
        }
        case TYPE_MEMORY:
        {
            success = RWS_TRUE;
            break;
        }
        case TYPE_CUSTOM:
        {
            success = m_data.custom.seek(position, m_data.custom.userdata);
            break;
        }
        }

        if (success)
        {
            m_position = position;
        }

        return success;
    }

    UInt32 Stream::Read(void* buffer, UInt32 length)
    {
        if (m_type == TYPE_NA)
        {
            return 0;
        }

        if (m_accessType != ACCESS_READ)
        {
            return 0;
        }

        UInt32 bytesRead = 0;

        switch (m_type)
        {
        case TYPE_FILE:
        {
            bytesRead = (UInt32)fread(buffer, 1, length, m_data.file.fp);
            break;
        }
        case TYPE_MEMORY:
        {
            if (m_position + length > m_data.memory.length)
            {
                length = m_data.memory.length - m_position;
            }

            if (memcpy(buffer, m_data.memory.start + m_position, length) == RWS_NULL)
            {
                bytesRead = 0;
            }
            else
            {
                bytesRead = length;
            }

            break;
        }
        case TYPE_CUSTOM:
        {
            bytesRead = m_data.custom.read(buffer, length, m_data.custom.userdata);
            break;
        }
        }

        m_position += bytesRead;

        return bytesRead;
    }

    UInt32 Stream::Write(const void* buffer, UInt32 length)
    {
        if (m_type == TYPE_NA)
        {
            return 0;
        }

        if (m_accessType != ACCESS_WRITE && m_accessType != ACCESS_APPEND)
        {
            return 0;
        }

        UInt32 bytesWritten = 0;

        switch (m_type)
        {
        case TYPE_FILE:
        {
            bytesWritten = (UInt32)fwrite(buffer, length, 1, m_data.file.fp);
            break;
        }
        case TYPE_MEMORY:
        {
            if (m_accessType == ACCESS_APPEND) // currently unsupported
            {
                bytesWritten = 0;
                break;
            }

            if (m_position + length > m_data.memory.length)
            {
                length = m_data.memory.length - m_position;
            }

            if (memcpy(m_data.memory.start + m_position, buffer, length) == RWS_NULL)
            {
                bytesWritten = 0;
            }
            else
            {
                bytesWritten = length;
            }

            break;
        }
        case TYPE_CUSTOM:
        {
            bytesWritten = m_data.custom.write(buffer, length, m_data.custom.userdata);
            break;
        }
        }

        return bytesWritten;
    }

    Bool Stream::Read8(void* buffer, UInt32 numBytes)
    {
        UInt32 bytesRead = Read(buffer, numBytes);

        return (bytesRead == numBytes);
    }

    Bool Stream::Read16(void* buffer, UInt32 numBytes)
    {
        UInt32 bytesRead = Read(buffer, numBytes);

        if (m_endian == LITTLE_ENDIAN)
        {
            Mem::LittleEndian16(buffer, bytesRead);
        }
        else
        {
            Mem::BigEndian16(buffer, bytesRead);
        }

        return (bytesRead == numBytes);
    }

    Bool Stream::Read32(void* buffer, UInt32 numBytes)
    {
        UInt32 bytesRead = Read(buffer, numBytes);

        if (m_endian == LITTLE_ENDIAN)
        {
            Mem::LittleEndian32(buffer, bytesRead);
        }
        else
        {
            Mem::BigEndian32(buffer, bytesRead);
        }

        return (bytesRead == numBytes);
    }

    Bool Stream::Write8(const void* buffer, UInt32 numBytes)
    {
        UInt32 bytesWritten = Write(buffer, numBytes);

        return (bytesWritten == numBytes);
    }

    Bool Stream::Write16(const void* buffer, UInt32 numBytes)
    {
        if (Mem::GetNativeEndian() == m_endian)
        {
            UInt32 bytesWritten = Write(buffer, numBytes);

            return (bytesWritten == numBytes);
        }
        else
        {
            UInt8 convertBuffer[256];
            UInt32 bytesLeft = numBytes;

            while (bytesLeft)
            {
                UInt32 bytesToCopy = (bytesLeft >= 256) ? 256 : bytesLeft;

                memcpy(convertBuffer, buffer, bytesToCopy);

                Mem::Swap16(convertBuffer, bytesToCopy);

                if (Write((const void*)convertBuffer, bytesToCopy) != bytesToCopy)
                {
                    return RWS_FALSE;
                }

                buffer = (UInt8*)buffer + bytesToCopy;
                bytesLeft -= bytesToCopy;
            }

            return RWS_TRUE;
        }
    }

    Bool Stream::Write32(const void* buffer, UInt32 numBytes)
    {
        if (Mem::GetNativeEndian() == m_endian)
        {
            UInt32 bytesWritten = Write(buffer, numBytes);

            return (bytesWritten == numBytes);
        }
        else
        {
            UInt8 convertBuffer[256];
            UInt32 bytesLeft = numBytes;

            while (bytesLeft)
            {
                UInt32 bytesToCopy = (bytesLeft >= 256) ? 256 : bytesLeft;

                memcpy(convertBuffer, buffer, bytesToCopy);

                Mem::Swap32(convertBuffer, bytesToCopy);

                if (Write((const void*)convertBuffer, bytesToCopy) != bytesToCopy)
                {
                    return RWS_FALSE;
                }

                buffer = (UInt8*)buffer + bytesToCopy;
                bytesLeft -= bytesToCopy;
            }

            return RWS_TRUE;
        }
    }

    Bool Stream::ReadChunkHeader(ChunkHeader* header)
    {
        return Read((UInt32*)header, sizeof(ChunkHeader));
    }

    Bool Stream::WriteChunkHeader(ChunkHeader* header)
    {
        return Write((UInt32*)header, sizeof(ChunkHeader));
    }

    Chunk* Stream::ReadChunk(Chunk* parent)
    {
        ChunkHeader header;

        if (!ReadChunkHeader(&header))
        {
            return RWS_NULL;
        }

        UInt32 end = Tell() + header.length;
        Chunk* chunk = RWS_NULL;

        if (s_chunkTypes.find(header.type) != s_chunkTypes.end())
        {
            ChunkType& chunkType = s_chunkTypes[header.type];
            ChunkConstructor constructor = RWS_NULL;

            if (parent && chunkType.constructors.find(parent->GetType()) != chunkType.constructors.end())
            {
                constructor = chunkType.constructors[parent->GetType()];
            }
            else if (chunkType.constructors.find(ID_NAOBJECT) != chunkType.constructors.end())
            {
                constructor = chunkType.constructors[ID_NAOBJECT];
            }

            if (constructor)
            {
                chunk = constructor();
            }
        }

        if (!chunk)
        {
            chunk = new DefaultChunk();
        }

        if (parent)
        {
            parent->AddChild(chunk);
        }

        chunk->SetType(header.type);
        chunk->SetVersion(LibraryIDToVersion(header.libraryID), RWS_FALSE);
        chunk->SetBuildNum(LibraryIDToBuildNum(header.libraryID), RWS_FALSE);
        chunk->Read(this, header.length);

        if (chunk->IsComplex())
        {
            while (Tell() < end)
            {
                ReadChunk(chunk);
            }
        }

        Seek(end);

        return chunk;
    }

    Bool Stream::WriteChunk(Chunk* chunk)
    {
        if (!chunk)
        {
            return RWS_FALSE;
        }

        UInt32 headerPos = Tell();

        ChunkHeader header;
        header.type = chunk->GetType();
        header.length = 0;
        header.libraryID = MakeLibraryID(chunk->GetVersion(), chunk->GetBuildNum());

        if (!WriteChunkHeader(&header))
        {
            return RWS_FALSE;
        }

        UInt32 start, end;

        start = Tell();

        chunk->Write(this);

        if (chunk->IsComplex())
        {
            Chunk* child = chunk->GetFirstChild();

            while (child)
            {
                WriteChunk(child);
                child = child->GetNext();
            }
        }

        end = Tell();

        header.length = end - start;

        Seek(headerPos);

        if (!WriteChunkHeader(&header))
        {
            return RWS_FALSE;
        }

        Seek(end);

        return RWS_TRUE;
    }

}