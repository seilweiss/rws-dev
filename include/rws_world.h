#pragma once

#include "rws/world/world_common.h"

#include "rws/world/chunk_atomic.h"
#include "rws/world/chunk_binmesh.h"
#include "rws/world/chunk_clump.h"
#include "rws/world/chunk_geometry.h"
#include "rws/world/chunk_geometrylist.h"
#include "rws/world/chunk_material.h"
#include "rws/world/chunk_materiallist.h"
#include "rws/world/chunk_nativedata.h"

namespace Rws {

    namespace WorldPlugin {

        inline void Register()
        {
            Atomic::Register();
            AtomicStruct::Register();
            BinMesh::Register();
            Clump::Register();
            ClumpStruct::Register();
            Geometry::Register();
            GeometryStruct::Register();
            GeometryList::Register();
            GeometryListStruct::Register();
            Material::Register();
            MaterialStruct::Register();
            MaterialList::Register();
            MaterialListStruct::Register();
            NativeData::Register();
            NativeDataStruct::Register();
        }

        inline void Unregister()
        {
            Atomic::Unregister();
            AtomicStruct::Unregister();
            BinMesh::Unregister();
            Clump::Unregister();
            ClumpStruct::Unregister();
            Geometry::Unregister();
            GeometryStruct::Unregister();
            GeometryList::Unregister();
            GeometryListStruct::Unregister();
            Material::Unregister();
            MaterialStruct::Unregister();
            MaterialList::Unregister();
            MaterialListStruct::Unregister();
            NativeData::Unregister();
            NativeDataStruct::Unregister();
        }

    }

}