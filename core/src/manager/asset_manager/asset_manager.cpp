#include <core/base/tgaimage.h>
#include <manager/asset_manager/asset_manager.h>

namespace SRR {
    void BasicMaterial::registerRes(const std::string& res_name, Util::TGAImage* img) {
        m_res_map[res_name] = img;
    }

    std::optional<Util::TGAImage*> BasicMaterial::getRes(const std::string& res_name) {
        if (m_res_map.find(res_name) == m_res_map.end())
            return {};
        return m_res_map[res_name];
    }

    void BasicMaterial::setTexRes(Util::TGAImage* res) {
        m_res_map["texture"] = res;
    }

    void BasicMaterial::setNormalRes(Util::TGAImage* res) {
        m_res_map["normal_map"] = res;
    }

    // *************************************************************************************************

    AssetManager::AssetManager() {
    }

    AssetManager::~AssetManager() {
    }

    void AssetManager::init() {
        // TODO: register default materials here
    }

    void AssetManager::registerTexRes(const std::string& tex_name, const std::string& tex_path) {
        if (m_tex_map.find(tex_name) != m_tex_map.end())
            return;
        auto img = std::make_shared<Util::TGAImage>();
        img->read_tga_file(tex_path.c_str());
        img->flip_vertically();
        m_tex_map[tex_name] = img;
    }

    std::optional<Util::TGAImage*> AssetManager::getTexRes(const std::string& tex_name) {
        if (m_tex_map.find(tex_name) == m_tex_map.end())
            return {};
        return m_tex_map[tex_name].get();
    }

    void AssetManager::registerMatRes(
        glm::vec4   albedo,
        glm::vec3   r0,
        float       roughness,
        glm::mat4x4 tex_transform) {
        auto mat              = std::make_shared<BasicMaterial>();
        mat->m_diffuse_albedo = albedo;
        mat->m_fresnel_r0     = r0;
        mat->m_roughness      = roughness;
        mat->m_tex_transform  = tex_transform;
    }

    std::optional<BasicMaterial*> AssetManager::getMatRes(const std::string& mat_name) {
        if (m_mat_map.find(mat_name) == m_mat_map.end())
            return {};
        return m_mat_map[mat_name].get();
    }

} // namespace SRR
