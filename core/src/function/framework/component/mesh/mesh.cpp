#include <glm/glm.hpp>

#include <core/base/macro.h>
#include <function/framework/component/mesh/mesh.h>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#endif

namespace SRR {
    void Mesh::loadMeshFromObj(const std::filesystem::path& target_path) {
        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = "./"; // Path to material files

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(target_path.string().c_str(), reader_config)) {
            if (!reader.Error().empty()) {
                LOG_ERROR("TinyObjReader: {}", reader.Error());
            }
            exit(1);
        }

        if (!reader.Warning().empty()) {
            LOG_WARN("TinyObjReader: {}", reader.Warning());
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        // FIXME: Read Materials
        // auto& materials = reader.GetMaterials();

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                if (fv != 3)
                    LOG_FATAL("This face is not triangle!!!");

                FaceDataDefinition face;

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    MeshVertexDataDefinition vert;

                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t  vx  = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t  vy  = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t  vz  = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                    vert.m_pos = glm::vec3(vx, vy, vz);

                    // Check if `normal_index` is zero or positive. negative = no normal data
                    if (idx.normal_index >= 0) {
                        tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

                        vert.m_normal = glm::vec3(nx, ny, nz);

                        // construct tangent
                        glm::vec3 P  = vert.m_pos;
                        glm::vec3 N  = vert.m_normal;
                        glm::vec4 up = {0.0f, 1.0f, 0.0f, 0.0f};
                        if (fabsf(glm::dot(N, glm::vec3(up))) < 1.0f - 0.001f) {
                            vert.m_tangent = glm::normalize(glm::cross(glm::vec3(up), N));
                        }
                        else {
                            up             = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
                            vert.m_tangent = glm::normalize(glm::cross(glm::vec3(up), N));
                        }
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                    if (idx.texcoord_index >= 0) {
                        tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

                        vert.m_uv = glm::vec2(tx, ty);
                    }

                    face.m_verts[v] = vert;

                    // Optional: vertex colors
                    // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                    // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                    // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
                }

                m_mesh_impl.m_faces.push_back(face);

                index_offset += fv;
            }
        }
        setDirtyFlag(true);
    }
} // namespace SRR
