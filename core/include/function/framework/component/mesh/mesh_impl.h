#pragma once

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <tiny_obj_loader.h>

namespace SRR {
    struct MeshVertexDataDefinition {
        glm::vec3 m_pos;     // position
        glm::vec3 m_normal;  // normal
        glm::vec3 m_tangent; // tangent
        glm::vec2 m_uv;      // UV coordinates
    };

    // FIXME: only support triangle
    struct FaceDataDefinition {
        MeshVertexDataDefinition m_verts[3];
    };

    struct MeshImpl {
        std::vector<FaceDataDefinition> m_faces;
    };
} // namespace SRR
