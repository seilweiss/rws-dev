#include "rws/hanim/chunk_hanim.h"

namespace Rws {

    void HAnimHierarchy::Read(Stream* stream, UInt32 length)
    {
        Int32 numNodes;

        stream->Read(&version);
        stream->Read(&nodeID);
        stream->Read(&numNodes);

        if (numNodes > 0)
        {
            stream->Read(&flags);
            stream->Read(&keyFrameSize);

            nodes.reserve(numNodes);

            for (Int32 i = 0; i < numNodes; i++)
            {
                NodeInfo node;

                stream->Read(&node.nodeID);
                stream->Read(&node.nodeIndex);
                stream->Read(&node.flags);

                nodes.push_back(node);
            }
        }
    }

    void HAnimHierarchy::Write(Stream* stream)
    {
        Int32 numNodes = (Int32)nodes.size();

        stream->Write(&version);
        stream->Write(&nodeID);
        stream->Write(&numNodes);

        if (numNodes > 0)
        {
            stream->Write(&flags);
            stream->Write(&keyFrameSize);

            for (NodeInfo& node : nodes)
            {
                stream->Write(&node.nodeID);
                stream->Write(&node.nodeIndex);
                stream->Write(&node.flags);
            }
        }
    }

}