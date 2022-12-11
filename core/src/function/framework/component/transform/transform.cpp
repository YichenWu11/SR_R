#include <function/framework/component/transform/transform.h>

namespace SRR {
    void Transform::loadTransform(const std::filesystem::path& target_path) {
        // TODO: load Transform from json (maybe)
    }

    void Transform::setTransform(glm::vec3 p, glm::vec3 s, glm::vec3 r) {
        m_transform_impl.m_pos      = p;
        m_transform_impl.m_scale    = s;
        m_transform_impl.m_rotation = glm::radians(r);
        setDirtyFlag(true);
    }

    glm::mat4x4 Transform::getWorldMat() {
        glm::mat4x4 world;
        glm::scale(world, m_transform_impl.m_scale);
        world = glm::mat4_cast(m_transform_impl.m_rotation) * world;
        glm::translate(world, m_transform_impl.m_pos);
        return world;
    }

    void Transform::setPos(glm::vec3 p) {
        m_transform_impl.m_pos = p;
        setDirtyFlag(true);
    }

    void Transform::setScale(glm::vec3 s) {
        m_transform_impl.m_scale = s;
        setDirtyFlag(true);
    }

    void Transform::setRotation(glm::vec3 r) {
        m_transform_impl.m_rotation = r;
        setDirtyFlag(true);
    }

} // namespace SRR