#pragma once

#include "rws/core/stream.h"

namespace Rws {

    struct V2d
    {
        Real x, y;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Write32(this, sizeof(*this));
        }
    };

    struct V3d
    {
        Real x, y, z;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Write32(this, sizeof(*this));
        }
    };

    struct Matrix
    {
        V3d right;
        UInt32 flags;
        V3d up;
        UInt32 pad1;
        V3d at;
        UInt32 pad2;
        V3d pos;
        UInt32 pad3;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }
    };

    struct Sphere
    {
        V3d center;
        Real radius;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Write32(this, sizeof(*this));
        }
    };

    struct TexCoords
    {
        Real u, v;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Write32(this, sizeof(*this));
        }
    };

    struct SurfaceProperties
    {
        Real ambient, specular, diffuse;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Write32(this, sizeof(*this));
        }
    };

    struct RGBA
    {
        UInt8 red, green, blue, alpha;

        void Read(Stream* stream)
        {
            stream->Read8(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Write8(this, sizeof(*this));
        }
    };

    struct RGBAReal
    {
        Real red, green, blue, alpha;

        void Read(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }

        void Write(Stream* stream)
        {
            stream->Read32(this, sizeof(*this));
        }
    };

}