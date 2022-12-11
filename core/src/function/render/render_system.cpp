#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>

#include <function/global/global_context.h>
#include <function/render/render_system.h>
#include <function/render/window_system.h>

namespace SRR {
    RenderSystem::RenderSystem() {
    }

    RenderSystem::~RenderSystem() {
    }

    void RenderSystem::init() {
        // register resources
        registerRes(
            "main",
            g_runtime_global_context.m_window_system->getWidth(),
            g_runtime_global_context.m_window_system->getHeight(),
            Util::TGAImage::Format::RGB);
    }

    void RenderSystem::registerRes(
        const std::string&     name,
        int                    width,
        int                    height,
        Util::TGAImage::Format format) {
        if (m_res_map.find(name) != m_res_map.end())
            return;
        m_res_map[name] = std::make_shared<Util::TGAImage>(width, height, format);
    }

    std::optional<Util::TGAImage*> RenderSystem::getRes(const std::string& name) {
        if (m_res_map.find(name) != m_res_map.end())
            return m_res_map[name].get();
        return {};
    }

    void RenderSystem::render(Util::TGAImage* target) {
        // TODO: Do Render Part Here
        static float cnt = 0.0f;

        switch (m_pipeline) {
            case RENDER_PIPELINE::FORWARD_PIPELINE:
                tbb::parallel_for(tbb::blocked_range2d<size_t>(0, target->get_width(), 0, target->get_height()),
                                  [&](tbb::blocked_range2d<size_t> r) {
                    for (size_t i = r.rows().begin(); i < r.rows().end(); ++i) {
                        for (size_t j = r.cols().begin(); j < r.cols().end(); ++j) {
                            target->set(i, j,
                                        Util::TGAColor(
                                            std::sin(i + cnt) * 255,
                                            std::cos(j + cnt) * 255,
                                            std::sin(j + cnt) * 255));
                        }
                    }
                });
                break;
            case RENDER_PIPELINE::DEFERRED_PIPELINE:
                // TODO: Impl deferred rendering
                break;
            default:
                break;
        }

        cnt += 0.5f;
    }
} // namespace SRR
