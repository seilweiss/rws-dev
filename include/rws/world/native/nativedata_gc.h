#pragma once

#include "nativedata_platform.h"

#include <vector>

namespace Rws {

    namespace GameCube {

        enum GXAttr
        {
            GX_VA_PNMTXIDX = 0,
            GX_VA_TEX0MTXIDX = 1,
            GX_VA_TEX1MTXIDX = 2,
            GX_VA_TEX2MTXIDX = 3,
            GX_VA_TEX3MTXIDX = 4,
            GX_VA_TEX4MTXIDX = 5,
            GX_VA_TEX5MTXIDX = 6,
            GX_VA_TEX6MTXIDX = 7,
            GX_VA_TEX7MTXIDX = 8,
            GX_VA_POS = 9,
            GX_VA_NRM = 10,
            GX_VA_CLR0 = 11,
            GX_VA_CLR1 = 12,
            GX_VA_TEX0 = 13,
            GX_VA_TEX1 = 14,
            GX_VA_TEX2 = 15,
            GX_VA_TEX3 = 16,
            GX_VA_TEX4 = 17,
            GX_VA_TEX5 = 18,
            GX_VA_TEX6 = 19,
            GX_VA_TEX7 = 20,
            GX_POS_MTX_ARRAY = 21,
            GX_NRM_MTX_ARRAY = 22,
            GX_TEX_MTX_ARRAY = 23,
            GX_LIGHT_ARRAY = 24,
            GX_VA_NBT = 25,
            GX_VA_MAX_ATTR = 26,
            GX_VA_NULL = 0xff
        };

        enum GXAttrType
        {
            GX_NONE = 0,
            GX_DIRECT = 1,
            GX_INDEX8 = 2,
            GX_INDEX16 = 3
        };

        enum GXPrimitive
        {
            GX_POINTS = 0xb8,
            GX_LINES = 0xa8,
            GX_LINESTRIP = 0xb0,
            GX_TRIANGLES = 0x90,
            GX_TRIANGLESTRIP = 0x98,
            GX_TRIANGLEFAN = 0xa0,
            GX_QUADS = 0x80
        };

        enum GXVtxFmt
        {
            GX_VTXFMT0 = 0,
            GX_VTXFMT1 = 1,
            GX_VTXFMT2 = 2,
            GX_VTXFMT3 = 3,
            GX_VTXFMT4 = 4,
            GX_VTXFMT5 = 5,
            GX_VTXFMT6 = 6,
            GX_VTXFMT7 = 7,
            GX_MAX_VTXFMT = 8
        };

        struct VertexDescriptor
        {
            GXAttr attr;
            UInt8 stride;
            GXAttrType type;
            UInt8 unknown;
        };

        struct IndexBuffer
        {
            GXPrimitive type;
            GXVtxFmt vtxfmt;
        };

    }

    class NativeDataGameCube : public NativeDataPlatform
    {
        RWS_NATIVEDATAPLATFORM(NativeDataGameCube, ID_GAMECUBE)

    public:
        UInt16 unknown1;
        UInt16 meshIndex;
        UInt32 unknown2;
        std::vector<GameCube::VertexDescriptor> attributes;
        std::vector<GameCube::IndexBuffer> indexBuffers;

        void Read(Stream* stream, UInt32 length, NativeData* nativeData) override;
        void Write(Stream* stream, NativeData* nativeData);
    };

}