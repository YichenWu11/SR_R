#pragma once

#include <filesystem>

#include <function/framework/component/component.h>
#include <function/framework/component/mesh/mesh_impl.h>

// FIXME: Load .obj only
namespace SRR {
    class Mesh : public Component {
    public:
        Mesh(const std::string& n = "Mesh") :
            Component(n) {}
        ~Mesh() {}

        std::any getImpl() override { return m_mesh_impl; }

    public:
        void loadMeshFromObj(const std::filesystem::path& target_path);

    private:
        MeshImpl m_mesh_impl;
    };
} // namespace SRR
