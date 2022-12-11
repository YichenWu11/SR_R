#pragma once

#include <filesystem>

#include <function/framework/component/component.h>
#include <function/framework/component/transform/transform_impl.h>

namespace SRR {
    class Transform : public Component {
    public:
        Transform(const std::string& n = "Transform") :
            Component(n) {}
        ~Transform() {}

        std::any getImpl() override { return m_transform_impl; }

    public:
        void        loadTransform(const std::filesystem::path& target_path);
        void        setTransform(glm::vec3 p, glm::vec3 s, glm::vec3 r);
        glm::mat4x4 getWorldMat();

        void setPos(glm::vec3 p);
        void setScale(glm::vec3 s);
        void setRotation(glm::vec3 r);

    private:
        TransformImpl m_transform_impl;
    };
} // namespace SRR
