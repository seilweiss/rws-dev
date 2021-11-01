#pragma once

#include "rws/core/stream.h"

namespace Rws {

    class ByteArray
    {
    public:
        ByteArray();
        ~ByteArray();

        UInt8* GetData() const { return m_data; }
        UInt32 GetLength() const { return m_length; }

        void SetData(const UInt8* data, UInt32 length = 0); // Makes a copy of the data

        void Read(Stream* stream, UInt32 length);
        void Write(Stream* stream);

    private:
        UInt8* m_data;
        UInt32 m_length;
    };

}