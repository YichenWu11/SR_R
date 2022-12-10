#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include <core/base/tgaimage.h>

namespace SRR::Util {
    class Color {
    public:
        Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
        Color(const glm::vec3&);
        Color(const glm::vec4&);

        Color(const Color&);
        Color& operator=(const Color&);
        Color(Color&&) = default;
        Color& operator=(Color&&) = default;

        ~Color() = default;

        operator glm::vec4();
        operator TGAColor();

        bool operator==(const Color&) const;
        Color operator+(const Color&) const;
        Color operator*(const Color&) const;

        float& r() { return m_value.r; }
        float r() const { return m_value.r; }
        float& g() { return m_value.g; }
        float g() const { return m_value.g; }
        float& b() { return m_value.b; }
        float b() const { return m_value.b; }
        float& a() { return m_value.a; }
        float a() const { return m_value.a; }

        int length() const { return m_value.length(); }

    private:
        TGAColor toTGAColor();

    private:
        glm::vec4 m_value;
    };
} // namespace SRR::Util
