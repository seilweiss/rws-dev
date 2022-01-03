#pragma once

#include "rws/core/stream.h"

namespace Rws {

	enum TextureFilterMode
	{
		FILTER_NA = 0,
		FILTER_NEAREST = 1,
		FILTER_LINEAR = 2,
		FILTER_MIPNEAREST = 3,
		FILTER_MIPLINEAR = 4,
		FILTER_LINEARMIPNEAREST = 5,
		FILTER_LINEARMIPLINEAR = 6,
		FILTER_MASK = 0xFF
	};

	enum TextureAddressMode
	{
		ADDRESS_NA = 0,
		ADDRESS_WRAP = 1,
		ADDRESS_MIRROR = 2,
		ADDRESS_CLAMP = 3,
		ADDRESS_BORDER = 4,
		ADDRESS_UMASK = 0xF00,
		ADDRESS_VMASK = 0xF000,
		ADDRESS_MASK = (ADDRESS_UMASK | ADDRESS_VMASK)
	};

	enum RasterFormat
	{
		RASTERFORMAT_DEFAULT = 0x0000,
		RASTERFORMAT_1555 = 0x0100,
		RASTERFORMAT_565 = 0x0200,
		RASTERFORMAT_4444 = 0x0300,
		RASTERFORMAT_LUM8 = 0x0400,
		RASTERFORMAT_8888 = 0x0500,
		RASTERFORMAT_888 = 0x0600,
		RASTERFORMAT_16 = 0x0700,
		RASTERFORMAT_24 = 0x0800,
		RASTERFORMAT_32 = 0x0900,
		RASTERFORMAT_555 = 0x0a00,
		RASTERFORMAT_AUTOMIPMAP = 0x1000,
		RASTERFORMAT_PAL8 = 0x2000,
		RASTERFORMAT_PAL4 = 0x4000,
		RASTERFORMAT_MIPMAP = 0x8000,
		RASTERFORMAT_PIXELFORMATMASK = 0x0f00,
		RASTERFORMAT_MASK = 0xff00
	};

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

		void Read(Stream* stream, RasterFormat format)
		{
			switch (format & RASTERFORMAT_PIXELFORMATMASK)
			{
			case RASTERFORMAT_1555:
			{
				UInt16 val;
				stream->Read(&val);
				red = (val >> 11) & 0x1F;
				green = (val >> 6) & 0x1F;
				blue = (val >> 1) & 0x1F;
				alpha = val & 0x1;
				break;
			}
			case RASTERFORMAT_565:
			{
				UInt16 val;
				stream->Read(&val);
				red = (val >> 11) & 0x1F;
				green = (val >> 5) & 0x3F;
				blue = val & 0x1F;
				alpha = 255;
				break;
			}
			case RASTERFORMAT_4444:
			{
				UInt16 val;
				stream->Read(&val);
				red = (val >> 12) & 0xF;
				green = (val >> 8) & 0xF;
				blue = (val >> 4) & 0xF;
				alpha = val & 0xF;
				break;
			}
			case RASTERFORMAT_LUM8:
			{
				UInt8 val;
				stream->Read(&val);
				red = val;
				green = val;
				blue = val;
				alpha = val;
				break;
			}
			case RASTERFORMAT_8888:
			{
				stream->Read(&red);
				stream->Read(&green);
				stream->Read(&blue);
				stream->Read(&alpha);
				break;
			}
			case RASTERFORMAT_888:
			{
				stream->Read(&red);
				stream->Read(&green);
				stream->Read(&blue);
				alpha = 255;
				stream->Skip(1);
				break;
			}
			case RASTERFORMAT_16:
			{
				red = 255;
				green = 255;
				blue = 255;
				alpha = 255;
				stream->Skip(2);
				break;
			}
			case RASTERFORMAT_24:
			{
				red = 255;
				green = 255;
				blue = 255;
				alpha = 255;
				stream->Skip(4);
				break;
			}
			case RASTERFORMAT_32:
			{
				red = 255;
				green = 255;
				blue = 255;
				alpha = 255;
				stream->Skip(4);
				break;
			}
			case RASTERFORMAT_555:
			{
				UInt16 val;
				stream->Read(&val);
				red = (val >> 10) & 0x1F;
				green = (val >> 5) & 0x1F;
				blue = val & 0x1F;
				alpha = 255;
				break;
			}
			}
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