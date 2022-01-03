#include "rws/core/chunk_texture.h"

namespace Rws {

    void TextureStruct::Read(Stream* stream, UInt32 length)
    {
        UInt32 filterAndAddress;
        stream->Read(&filterAndAddress);

        filtering = (TextureFilterMode)(filterAndAddress & FILTER_MASK);
        addressingU = (TextureAddressMode)((filterAndAddress >> 8) & 0xF);
        addressingV = (TextureAddressMode)((filterAndAddress >> 12) & 0xF);
        flags = (StreamFlags)((filterAndAddress >> 16) & 0xFF);
    }

    void TextureStruct::Write(Stream* stream)
    {
        UInt32 filterAndAddress = (filtering) | (addressingU << 8) | (addressingV << 12) | (flags << 16);
        stream->Write(&filterAndAddress);
    }

}