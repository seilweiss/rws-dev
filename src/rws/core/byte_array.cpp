#include "rws/core/byte_array.h"

#include <cstdlib>
#include <cstring>

namespace Rws {

    ByteArray::ByteArray()
    {
        m_data = RWS_NULL;
        m_length = 0;
    }

    ByteArray::~ByteArray()
    {
        if (m_data)
        {
            free(m_data);
        }
    }

    void ByteArray::SetData(const UInt8* data, UInt32 length)
    {
        if (m_data)
        {
            free(m_data);
        }

        if (data && length > 0)
        {
            m_data = (UInt8*)malloc(length);
            m_length = length;

            if (m_data)
            {
                memcpy(m_data, data, length);
            }
        }
        else
        {
            m_data = RWS_NULL;
            m_length = 0;
        }
    }

    void ByteArray::Read(Stream* stream, UInt32 length)
    {
        if (m_data)
        {
            free(m_data);
        }

        if (length > 0)
        {
            m_data = (UInt8*)malloc(length);
            m_length = length;

            if (m_data)
            {
                stream->Read((void*)m_data, length);
            }
        }
        else
        {
            m_data = RWS_NULL;
            m_length = 0;
        }
    }

    void ByteArray::Write(Stream* stream)
    {
        if (m_data && m_length > 0)
        {
            stream->Write((const void*)m_data, m_length);
        }
    }

}