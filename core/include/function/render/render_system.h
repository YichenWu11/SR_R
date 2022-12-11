#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>

#include <core/base/tgaimage.h>

namespace SRR {
    class RenderSystem {
    public:
        enum class RENDER_PIPELINE : uint8_t {
            FORWARD_PIPELINE = 0,
            DEFERRED_PIPELINE,
            COUNT
        };

    public:
        RenderSystem();
        ~RenderSystem();

        void                           init();
        void                           registerRes(const std::string& name, int width, int height, Util::TGAImage::Format format);
        std::optional<Util::TGAImage*> getRes(const std::string& name);
        void                           render(Util::TGAImage*);

        void setRenderPipeline(RENDER_PIPELINE type) { m_pipeline = type; }

    private:
        std::map<std::string, std::shared_ptr<Util::TGAImage>> m_res_map;
        RENDER_PIPELINE                                        m_pipeline{RENDER_PIPELINE::FORWARD_PIPELINE};
    };
} // namespace SRR