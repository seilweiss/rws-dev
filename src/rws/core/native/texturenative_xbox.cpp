#include "rws/core/native/texturenative_xbox.h"

namespace Rws {

    namespace {

        // https://osdn.net/projects/magic-rw/scm/svn/blobs/head/rwlib/src/txdread.xbox.swizzle.cpp
        // https://osdn.net/projects/magic-rw/scm/svn/blobs/head/rwlib/vendor/xdk/XGraphics.h
        void unswizzle(RGBA* dst, const RGBA* src, UInt32 width, UInt32 height)
        {
            UInt32 maskU = 0;
            UInt32 maskV = 0;

            {
                UInt32 i = 1;
                UInt32 j = 1;
                UInt32 k;

                do
                {
                    k = 0;

                    if (i < width)
                    {
                        maskU |= j;
                        k = (j <<= 1);
                    }

                    if (i < height)
                    {
                        maskV |= j;
                        k = (j <<= 1);
                    }

                    i <<= 1;
                } while (k);
            }

            UInt32 v = 0;

            for (UInt32 y = 0; y < height; y++)
            {
                UInt32 u = 0;

                for (UInt32 x = 0; x < width; x++)
                {
                    UInt32 swizzleIndex = u | v;
                    UInt32 swizzleX = swizzleIndex % width;
                    UInt32 swizzleY = swizzleIndex / width;

                    if (x < width && y < height)
                    {
                        RGBA* dstCol = &dst[y * width + x];

                        if (swizzleX < width && swizzleY < height)
                        {
                            const RGBA* srcCol = &src[swizzleY * width + swizzleX];

                            *dstCol = *srcCol;
                        }
                        else
                        {
                            dstCol->red = 0;
                            dstCol->green = 0;
                            dstCol->blue = 0;
                            dstCol->alpha = 0;
                        }
                    }

                    u = (u - maskU) & maskU;
                }

                v = (v - maskV) & maskV;
            }
        }

        void RGBAToBGRA(RGBA* color)
        {
            UInt8 red = color->red;
            color->red = color->blue;
            color->blue = red;
        }

    }

    struct Header
    {
        UInt32 filterFlags;
        Char name[32];
        Char maskName[32];
        UInt32 rasterFormat;
        UInt16 hasAlpha;
        UInt16 isCubeMap;
        UInt16 width;
        UInt16 height;
        UInt8 depth;
        UInt8 mipmapCount;
        UInt8 rasterType;
        UInt8 dxtCompression;
        UInt32 unknown;

        void Read(Stream* stream)
        {
            stream->Read(&filterFlags);
            stream->Read(name, sizeof(name));
            stream->Read(maskName, sizeof(maskName));
            stream->Read(&rasterFormat);
            stream->Read(&hasAlpha);
            stream->Read(&isCubeMap);
            stream->Read(&width);
            stream->Read(&height);
            stream->Read(&depth);
            stream->Read(&mipmapCount);
            stream->Read(&rasterType);
            stream->Read(&dxtCompression);
            stream->Read(&unknown);
        }

        void Write(Stream* stream)
        {
            stream->Write(&filterFlags);
            stream->Write(name, sizeof(name));
            stream->Write(maskName, sizeof(maskName));
            stream->Write(&rasterFormat);
            stream->Write(&hasAlpha);
            stream->Write(&isCubeMap);
            stream->Write(&width);
            stream->Write(&height);
            stream->Write(&depth);
            stream->Write(&mipmapCount);
            stream->Write(&rasterType);
            stream->Write(&dxtCompression);
            stream->Write(&unknown);
        }
    };

    void TextureNativeXbox::Read(Stream* stream, UInt32 length, TextureNative* textureNative)
    {
        // TODO:
        // * DXT compression
        // * Mipmaps

        Endian oldEndian = stream->GetEndian();

        stream->SetEndian(LITTLE_ENDIAN);

        Header header;
        header.Read(stream);

        textureNative->filtering = (TextureFilterMode)(header.filterFlags & FILTER_MASK);
        textureNative->addressingU = (TextureAddressMode)((header.filterFlags >> 8) & 0xF);
        textureNative->addressingV = (TextureAddressMode)((header.filterFlags >> 12) & 0xF);

        memcpy(textureNative->name, header.name, sizeof(textureNative->name));
        memcpy(textureNative->maskName, header.maskName, sizeof(textureNative->maskName));

        textureNative->rasterFormat = (RasterFormat)header.rasterFormat;
        textureNative->hasAlpha = header.hasAlpha != 0;
        textureNative->width = header.width;
        textureNative->height = header.height;
        textureNative->depth = header.depth;

        dxtCompression = header.dxtCompression;

        UInt32 palCount = 0;

        if (header.rasterFormat & RASTERFORMAT_PAL8)
        {
            palCount = 256;
        }
        else if (header.rasterFormat & RASTERFORMAT_PAL4)
        {
            palCount = 32;
        }

        UInt32 dataSize = header.width * header.height;
        std::vector<RGBA> swizzledTexels;

        if (palCount)
        {
            std::vector<RGBA> palette;

            for (UInt32 i = 0; i < palCount; i++)
            {
                RGBA color;
                color.Read(stream, textureNative->rasterFormat);
                RGBAToBGRA(&color);
                palette.push_back(color);
            }

            for (UInt32 i = 0; i < dataSize; i++)
            {
                UInt8 palIndex;
                stream->Read(&palIndex);
                swizzledTexels.push_back(palette[palIndex]);
            }
        }
        else
        {
            for (UInt32 i = 0; i < dataSize; i++)
            {
                RGBA color;
                color.Read(stream, textureNative->rasterFormat);
                RGBAToBGRA(&color);
                swizzledTexels.push_back(color);
            }
        }

        textureNative->texels.resize(swizzledTexels.size());

        unswizzle(textureNative->texels.data(), swizzledTexels.data(), textureNative->width, textureNative->height);

        stream->SetEndian(oldEndian);
    }

    void TextureNativeXbox::Write(Stream* stream, TextureNative* textureNative)
    {

    }

}