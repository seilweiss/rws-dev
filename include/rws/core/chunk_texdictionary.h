#pragma once

#include "rws/core/chunk.h"
#include "rws/core/chunk_texturenative.h"

namespace Rws {

    class TexDictionaryStruct;

    class TexDictionary : public Chunk
    {
        RWS_CHUNK(TexDictionary, ID_TEXDICTIONARY, ID_NAOBJECT, RWS_TRUE)

    public:
        TexDictionaryStruct* GetStruct() const { return GetChild<TexDictionaryStruct>(); }
        TextureNative* GetTextureNative(Int32 index) const { return GetChild<TextureNative>(index); }
        std::vector<TextureNative*> GetTextureNatives() const { return GetChildren<TextureNative>(); }
        UInt32 GetTextureNativeCount() const { return GetChildCount<TextureNative>(); }
    };

    class TexDictionaryStruct : public Chunk
    {
        RWS_CHUNK(TexDictionaryStruct, ID_STRUCT, ID_TEXDICTIONARY, RWS_FALSE)

    public:
        UInt32 deviceId;

        void Read(Stream* stream, UInt32 length) override;
        void Write(Stream* stream) override;
    };

}