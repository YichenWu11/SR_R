#pragma once

#include <memory>
#include <string>

namespace SRR {
    class LogSystem;
    class WindowSystem;
    class RenderSystem;

    // Manage the lifetime and creation/destruction order of all global system
    class RuntimeGlobalContext {
    public:
        // create all global systems and initialize these systems
        void startSystems(const std::string& root_path);
        // destroy all global systems
        void shutdownSystems();
        void initSystems(const std::string& root_path);

    public:
        std::shared_ptr<LogSystem>    m_logger_system;
        std::shared_ptr<WindowSystem> m_window_system;
        std::shared_ptr<RenderSystem> m_render_system;
    };

    extern RuntimeGlobalContext g_runtime_global_context;
} // namespace SRR
