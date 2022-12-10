#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>

#include <core/base/tgaimage.h>

namespace SRR {
    class RenderSystem {
    public:
        RenderSystem();
        ~RenderSystem();

        void                           init();
        void                           registerRes(const std::string& name, int width, int height, Util::TGAImage::Format format);
        std::optional<Util::TGAImage*> getRes(const std::string& name);
        void                           render(Util::TGAImage*);

    private:
        std::map<std::string, std::shared_ptr<Util::TGAImage>> m_res_map;
    };
} // namespace SRR