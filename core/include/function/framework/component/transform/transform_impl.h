#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SRR {
    struct TransformImpl {
        glm::vec3 m_pos{glm::vec3(0.0f)};
        glm::vec3 m_scale{glm::vec3(1.0f)};
        glm::quat m_rotation{glm::radians(glm::vec3(0.0f, 0.0f, 0.0f))};
    };
} // namespace SRR
