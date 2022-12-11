#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace SRR::Util {
    class TGAImage;
}

namespace SRR {
    struct BasicMaterial {
        glm::vec4                              m_diffuse_albedo{1.0f, 1.0f, 1.0f, 1.0f};
        glm::vec3                              m_fresnel_r0{0.01f, 0.01f, 0.01f};
        float                                  m_roughness{0.25f};
        glm::mat4x4                            m_tex_transform{glm::mat4(1.0f)};
        std::map<std::string, Util::TGAImage*> m_res_map;

        void                           registerRes(const std::string& res_name, Util::TGAImage* img);
        std::optional<Util::TGAImage*> getRes(const std::string& res_name);

        // util funcs
        void setTexRes(Util::TGAImage*);
        void setNormalRes(Util::TGAImage*);
    };

    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        void init();

        void                           registerTexRes(const std::string& tex_name, const std::string& tex_path);
        std::optional<Util::TGAImage*> getTexRes(const std::string& tex_name);

        void registerMatRes(
            glm::vec4   albedo        = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec3   r0            = glm::vec3(0.01f, 0.01f, 0.01f),
            float       roughness     = 0.25f,
            glm::mat4x4 tex_transform = glm::mat4(1.0f));
        std::optional<BasicMaterial*> getMatRes(const std::string& mat_name);

    private:
        std::map<std::string, std::shared_ptr<Util::TGAImage>> m_tex_map;
        std::map<std::string, std::shared_ptr<BasicMaterial>>  m_mat_map;
    };
} // namespace SRR
