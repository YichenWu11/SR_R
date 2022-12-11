#include <function/framework/component/material/material.h>

namespace SRR {
    void Material::setMat(BasicMaterial* p2mat) {
        m_material_impl.m_mat = p2mat;
        setDirtyFlag(true);
    }
} // namespace SRR
