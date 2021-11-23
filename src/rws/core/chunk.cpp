#include "rws/core/chunk.h"

#include "rws/core/version.h"
#include "rws/core/chunk_extension.h"

#include <cstdlib>
#include <cstring>

namespace Rws {

    Chunk::Chunk(UInt32 type)
    {
        m_type = type;
        m_version = Rws::GetDefaultVersion();
        m_buildNum = Rws::GetDefaultBuildNum();
        m_parent = RWS_NULL;
        m_prev = RWS_NULL;
        m_next = RWS_NULL;
        m_child = RWS_NULL;
    }

    Chunk::~Chunk()
    {
        if (m_parent)
        {
            m_parent->RemoveChild(this);
        }

        Chunk* child = m_child;

        while (child)
        {
            Chunk* next = child->m_next;
            delete child;
            child = next;
        }
    }

    void Chunk::SetVersion(UInt32 version, Bool recursive)
    {
        m_version = version;

        if (recursive)
        {
            Chunk* child = m_child;

            while (child)
            {
                child->SetVersion(version, RWS_TRUE);
                child = child->m_next;
            }
        }
    }

    void Chunk::SetBuildNum(UInt32 buildNum, Bool recursive)
    {
        m_buildNum = buildNum;

        if (recursive)
        {
            Chunk* child = m_child;

            while (child)
            {
                child->SetBuildNum(buildNum, RWS_TRUE);
                child = child->m_next;
            }
        }
    }

    Int32 Chunk::GetIndexInParent() const
    {
        if (m_parent)
        {
            return m_parent->GetChildIndex(this);
        }

        return -1;
    }

    Chunk* Chunk::GetChild(Int32 index) const
    {
        if (index < 0)
        {
            return RWS_NULL;
        }

        Chunk* child = m_child;

        while (child && index != 0)
        {
            child = child->m_next;
            index--;
        }

        return child;
    }

    Chunk* Chunk::GetChildByType(UInt32 type, Int32 index) const
    {
        if (index < 0)
        {
            return RWS_NULL;
        }

        Chunk* child = m_child;

        while (child)
        {
            if (child->m_type == type)
            {
                if (index == 0)
                {
                    break;
                }

                index--;
            }

            child = child->m_next;
        }

        return child;
    }

    Chunk* Chunk::GetLastChild() const
    {
        Chunk* last = m_child;

        while (last->m_next)
        {
            last = last->m_next;
        }

        return last;
    }

    std::vector<Chunk*> Chunk::GetChildren() const
    {
        std::vector<Chunk*> children;

        Chunk* child = m_child;

        while (child)
        {
            children.push_back(child);
            child = child->m_next;
        }

        return children;
    }

    std::vector<Chunk*> Chunk::GetChildrenByType(UInt32 type) const
    {
        std::vector<Chunk*> children;

        Chunk* child = m_child;

        while (child)
        {
            if (child->m_type == type)
            {
                children.push_back(child);
            }

            child = child->m_next;
        }

        return children;
    }

    Int32 Chunk::GetChildIndex(const Chunk* searchChild) const
    {
        if (!searchChild)
        {
            return -1;
        }

        if (searchChild->m_parent != this)
        {
            return -1;
        }

        Int32 index = 0;
        Chunk* child = m_child;

        while (child)
        {
            if (child == searchChild)
            {
                return index;
            }

            index++;
            child = child->m_next;
        }

        return -1;
    }

    UInt32 Chunk::GetChildCount() const
    {
        UInt32 count = 0;
        Chunk* child = m_child;

        while (child)
        {
            count++;
            child = child->m_next;
        }

        return count;
    }

    UInt32 Chunk::GetChildCountByType(UInt32 type) const
    {
        UInt32 count = 0;
        Chunk* child = m_child;

        while (child)
        {
            if (child->m_type == type)
            {
                count++;
            }

            child = child->m_next;
        }

        return count;
    }

    void Chunk::AddChild(Chunk* child)
    {
        if (!child)
        {
            return;
        }

        if (child->m_parent)
        {
            if (child->m_parent == this)
            {
                return;
            }

            child->m_parent->RemoveChild(child);
        }

        if (m_child)
        {
            Chunk* last = m_child;

            while (last->m_next)
            {
                last = last->m_next;
            }

            last->m_next = child;

            child->m_prev = last;
            child->m_next = RWS_NULL;
        }
        else
        {
            m_child = child;
            m_child->m_prev = RWS_NULL;
            m_child->m_next = RWS_NULL;
        }

        child->m_parent = this;
    }

    void Chunk::RemoveChild(Chunk* child)
    {
        if (!child)
        {
            return;
        }

        if (child->m_parent != this)
        {
            return;
        }

        if (child->m_prev)
        {
            child->m_prev->m_next = child->m_next;
        }

        if (child->m_next)
        {
            child->m_next->m_prev = child->m_prev;
        }

        child->m_prev = RWS_NULL;
        child->m_next = RWS_NULL;
        child->m_parent = RWS_NULL;
    }

    void Chunk::InsertChild(Chunk* child, Chunk* before)
    {
        if (!child)
        {
            return;
        }

        if (!before)
        {
            return;
        }

        if (child->m_parent)
        {
            if (child->m_parent == this)
            {
                MoveChild(child, before);
                return;
            }

            child->m_parent->RemoveChild(child);
        }

        if (before->m_prev)
        {
            before->m_prev->m_next = child;
        }

        child->m_prev = before->m_prev;
        child->m_next = before;
        child->m_parent = this;

        before->m_prev = child;
    }

    void Chunk::MoveChild(Chunk* child, Chunk* before)
    {
        if (!child)
        {
            return;
        }

        if (!before)
        {
            return;
        }

        if (child->m_parent != this)
        {
            return;
        }

        if (child->m_prev)
        {
            child->m_prev->m_next = child->m_next;
        }

        if (child->m_next)
        {
            child->m_next->m_prev = child->m_prev;
        }

        if (before->m_prev)
        {
            before->m_prev->m_next = child;
        }

        child->m_prev = before->m_prev;
        child->m_next = before;

        before->m_prev = child;
    }

    Chunk* Chunk::GetExtension(Int32 index) const
    {
        if (index < 0)
        {
            return RWS_NULL;
        }

        Extension* extension = GetChild<Extension>(0);

        while (extension)
        {
            Int32 count = (Int32)extension->GetChildCount();

            if (index < count)
            {
                return extension->GetChild(index);
            }

            index -= count;
            extension = (Extension*)extension->m_next;
        }

        return RWS_NULL;
    }

    Chunk* Chunk::GetExtensionByType(UInt32 type, Int32 index) const
    {
        Extension* extension = GetChild<Extension>(0);

        while (extension)
        {
            Int32 count = (Int32)extension->GetChildCountByType(type);

            if (index < count)
            {
                return extension->GetChildByType(type, index);
            }

            index -= count;
            extension = (Extension*)extension->m_next;
        }

        return RWS_NULL;
    }

    Chunk* Chunk::GetExtensionParent() const
    {
        Extension* extension = GetParentAs<Extension>();

        if (!extension)
        {
            return RWS_NULL;
        }

        return extension->GetParent();
    }

}