#pragma once

#include "rws/core/types.h"
#include "rws/core/stream.h"
#include "rws/core/ids.h"

#include <vector>

#define RWS_CHUNK(ClassName, type, parentType, isComplex)\
    public:\
        ClassName() : Chunk((type)) {}\
        static void Register() { Rws::Stream::RegisterChunkType((type), (parentType), [] { return (Chunk*)new ClassName; }); }\
        static void Unregister() { Rws::Stream::UnregisterChunkType((type), (parentType)); }\
        static const char* GetClassNameStatic() { return #ClassName; }\
        static UInt32 GetExpectedTypeStatic() { return (type); }\
        static UInt32 GetExpectedParentTypeStatic() { return (parentType); }\
        static Bool IsComplexStatic() { return (isComplex); }\
        virtual const char* GetClassName() const { return #ClassName; }\
        virtual UInt32 GetExpectedType() const { return (type); }\
        virtual UInt32 GetExpectedParentType() const { return (parentType); }\
        virtual Bool IsComplex() const { return (isComplex); }\
        virtual Bool IsCorrectType() const { return IsType((type)); }\
        virtual Bool IsParentCorrectType() const { return (parentType) == ID_NAOBJECT || (HasParent() && GetParent()->IsType((parentType))); }

namespace Rws {

    class Chunk
    {
    public:
        Chunk(UInt32 type);
        ~Chunk();

        template <class T> T* As() const { return IsType(T::GetExpectedTypeStatic()) ? (T*)this : RWS_NULL; }

        UInt32 GetType() const { return m_type; }
        void SetType(UInt32 type) { m_type = type; }
        Bool IsType(UInt32 type) const { return m_type == type; }
        UInt32 GetVersion() const { return m_version; }
        void SetVersion(UInt32 version, Bool recursive = RWS_TRUE);
        UInt32 GetBuildNum() const { return m_buildNum; }
        void SetBuildNum(UInt32 buildNum, Bool recursive = RWS_TRUE);

        Chunk* GetParent() const { return m_parent; }
        template <class T> T* GetParentAs() const { return m_parent ? m_parent->As<T>() : RWS_NULL; }
        Bool HasParent() const { return m_parent != RWS_NULL; }
        Chunk* GetPrevious() const { return m_prev; }
        template <class T> T* GetPreviousAs() const { return m_prev ? m_prev->As<T>() : RWS_NULL; }
        Chunk* GetNext() const { return m_next; }
        template<class T> T* GetNextAs() const { return m_next ? m_next->As<T>() : RWS_NULL; }
        Int32 GetIndexInParent() const;
        Chunk* GetChild(Int32 index) const;
        Chunk* GetChildByType(UInt32 type, Int32 index = 0) const;
        template <class T> T* GetChild(Int32 index = 0) const { return (T*)GetChildByType(T::GetExpectedTypeStatic(), index); }
        Chunk* GetFirstChild() const { return m_child; }
        Chunk* GetLastChild() const;
        std::vector<Chunk*> GetChildren() const;
        std::vector<Chunk*> GetChildrenByType(UInt32 type) const;

        template <class T> std::vector<T*> GetChildren() const
        {
            std::vector<Chunk*> children = GetChildrenByType(T::GetExpectedTypeStatic());
            std::vector<T*> inherited;

            for (Chunk* child : children)
            {
                inherited.push_back((T*)child);
            }

            return inherited;
        }

        Int32 GetChildIndex(const Chunk* child) const;
        Bool HasChild(Chunk* child) const { return child->m_parent == this; }
        UInt32 GetChildCount() const;
        UInt32 GetChildCountByType(UInt32 type) const;
        template <class T> UInt32 GetChildCount() const { return GetChildCountByType(T::GetExpectedTypeStatic()); }
        void AddChild(Chunk* child);
        void RemoveChild(Chunk* child);
        void RemoveChild(Int32 index) { RemoveChild(GetChild(index)); }
        void InsertChild(Chunk* child, Chunk* before);
        void InsertChild(Chunk* child, Int32 index) { InsertChild(child, GetChild(index)); }
        void MoveChild(Chunk* child, Chunk* before);
        void MoveChild(Chunk* child, Int32 index) { MoveChild(child, GetChild(index)); }

        Chunk* GetExtension(Int32 index) const;
        Chunk* GetExtensionByType(UInt32 type, Int32 index = 0) const;
        template <class T> T* GetExtension(Int32 index = 0) const { return (T*)GetExtensionByType(T::GetExpectedTypeStatic(), index); }
        Chunk* GetExtensionParent() const;
        template <class T> T* GetExtensionParentAs() const { Chunk* parent = GetExtensionParent(); return parent ? parent->As<T>() : RWS_NULL; }

        virtual void Read(Stream*, UInt32) {}
        virtual void Write(Stream*) {}

        virtual const char* GetClassName() const = 0;
        virtual UInt32 GetExpectedType() const = 0;
        virtual UInt32 GetExpectedParentType() const = 0;
        virtual Bool IsComplex() const = 0;
        virtual Bool IsCorrectType() const = 0;
        virtual Bool IsParentCorrectType() const = 0;

    private:
        UInt32 m_type;
        UInt32 m_version;
        UInt32 m_buildNum;
        Chunk* m_parent;
        Chunk* m_prev;
        Chunk* m_next;
        Chunk* m_child;
    };

}
