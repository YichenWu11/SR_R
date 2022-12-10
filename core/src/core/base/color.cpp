#include <core/base/color.h>

namespace SRR::Util {
    // constructor
    Color::Color(float r, float g, float b, float a) {
        m_value = glm::vec4(
            glm::clamp(r, 0.0f, 1.0f),
            glm::clamp(g, 0.0f, 1.0f),
            glm::clamp(b, 0.0f, 1.0f),
            glm::clamp(a, 0.0f, 1.0f));
    }

    Color::Color(const glm::vec3& v) :
        m_value(
            glm::clamp(v.r, 0.0f, 1.0f),
            glm::clamp(v.g, 0.0f, 1.0f),
            glm::clamp(v.b, 0.0f, 1.0f),
            1.0f) {}

    Color::Color(const glm::vec4& v) :
        m_value(
            glm::clamp(v.r, 0.0f, 1.0f),
            glm::clamp(v.g, 0.0f, 1.0f),
            glm::clamp(v.b, 0.0f, 1.0f),
            glm::clamp(v.a, 0.0f, 1.0f)) {}

    Color::Color(const Color& rhs) :
        m_value(rhs.m_value) {}

    Color& Color::operator=(const Color& rhs) {
        m_value = rhs.m_value;
        return *this;
    }

    // cast
    Color::operator TGAColor() {
        return toTGAColor();
    }

    Color::operator glm::vec4() {
        return m_value;
    }

    // operator
    bool Color::operator==(const Color& rhs) const {
        return m_value == rhs.m_value;
    }

    Color Color::operator+(const Color& rhs) const {
        return Color(m_value + rhs.m_value);
    }

    Color Color::operator*(const Color& rhs) const {
        return Color(m_value * rhs.m_value);
    }

    // util

    // TGAColor's Order is `BGRA`
    TGAColor Color::toTGAColor() {
        return TGAColor(
            static_cast<unsigned char>(m_value.r * 255),
            static_cast<unsigned char>(m_value.g * 255),
            static_cast<unsigned char>(m_value.b * 255),
            static_cast<unsigned char>(m_value.a * 255));
    }

} // namespace SRR::Util