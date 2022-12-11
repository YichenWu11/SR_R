#pragma once

#include <function/framework/component/component.h>
#include <function/framework/component/material/material_impl.h>

namespace SRR {
    class Material : public Component {
    public:
        Material(const std::string& n = "Material") :
            Component(n) {}
        ~Material() {}

        std::any getImpl() override { return m_material_impl; }

        void setMat(BasicMaterial* p2mat);

    private:
        MaterialImpl m_material_impl;
    };
} // namespace SRR
