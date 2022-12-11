#include <core/log/log_system.h>
#include <function/framework/scene/scene_manager.h>
#include <function/global/global_context.h>
#include <function/render/render_system.h>
#include <function/render/window_system.h>
#include <manager/asset_manager/asset_manager.h>

namespace SRR {
    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::startSystems(const std::string& root_path) {
        m_logger_system = std::make_shared<LogSystem>();
        m_window_system = std::make_shared<WindowSystem>();
        m_render_system = std::make_shared<RenderSystem>();
        m_asset_manager = std::make_shared<AssetManager>();
        m_scene_manager = std::make_shared<SceneManager>();
    }

    void RuntimeGlobalContext::shutdownSystems() {
        m_logger_system.reset();
        m_window_system.reset();
        m_render_system.reset();
        m_asset_manager.reset();
        m_scene_manager.reset();
    }

    void RuntimeGlobalContext::initSystems(const std::string& root_path) {
        SRR::WindowCreateInfo create_info;
        create_info.width  = 640;
        create_info.height = 480;
        create_info.title  = "Hello_World";
        create_info.path   = root_path;

        m_window_system->init(create_info);
        m_render_system->init();
        // TODO: Impl the `Init` of `m_asset_manager` and `m_scene_manager`
        m_asset_manager->init();
        m_scene_manager->init();
    }
} // namespace SRR
