#include "rws/core/chunk_texdictionary.h"

namespace Rws {

    void TexDictionaryStruct::Read(Stream* stream, UInt32 length)
    {
        UInt32 numTexturesAndDeviceId;
        stream->Read(&numTexturesAndDeviceId);

        deviceId = (numTexturesAndDeviceId >> 16) & 0xFFFF;
    }

    void TexDictionaryStruct::Write(Stream* stream)
    {
        TexDictionary* texDict = GetParentAs<TexDictionary>();
        UInt32 numTextures = texDict ? texDict->GetTextureNativeCount() : 0;
        UInt32 numTexturesAndDeviceId = ((numTextures & 0xFFFF) << 16) | (deviceId & 0xFFFF);

        stream->Write(&numTexturesAndDeviceId);
    }

}