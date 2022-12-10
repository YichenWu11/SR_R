#include <core/log/log_system.h>
#include <function/global/global_context.h>
#include <function/render/render_system.h>
#include <function/render/window_system.h>

namespace SRR {
    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::startSystems(const std::string& root_path) {
        m_logger_system = std::make_shared<LogSystem>();
        m_window_system = std::make_shared<WindowSystem>();
        m_render_system = std::make_shared<RenderSystem>();
    }

    void RuntimeGlobalContext::shutdownSystems() {
        m_logger_system.reset();
        m_window_system.reset();
        m_render_system.reset();
    }

    void RuntimeGlobalContext::initSystems(const std::string& root_path) {
        SRR::WindowCreateInfo create_info;
        create_info.width  = 640;
        create_info.height = 480;
        create_info.title  = "Hello_World";
        create_info.path   = root_path;

        m_window_system->init(create_info);
        m_render_system->init();
    }
} // namespace SRR
