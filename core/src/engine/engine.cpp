#include <core/base/macro.h>
#include <engine/engine.h>
#include <function/global/global_context.h>
#include <function/render/render_system.h>
#include <function/render/window_system.h>

namespace SRR {
    void Engine::startEngine(const std::string& root_path) {
        g_runtime_global_context.startSystems(root_path);
        g_runtime_global_context.initSystems(root_path);

        LOG_INFO("srr start");
    }

    void Engine::shutdownEngine() {
        g_runtime_global_context.m_window_system->outputRes(
            g_runtime_global_context.m_render_system->getRes("main").value());

        LOG_INFO("srr shutdown");

        g_runtime_global_context.shutdownSystems();
    }

    void Engine::init() {
        // do nothing
    }

    void Engine::clear() {
        // do nothing
    }

    void Engine::run() {
        std::shared_ptr<WindowSystem> window_system = g_runtime_global_context.m_window_system;
        ASSERT(window_system);
        window_system->resetTimer();

        while (!window_system->isShouldClose()) {
            const float delta_time = calculateDeltaTime();
            tickOneFrame(delta_time);
        }
    }

    void Engine::tickOneFrame(float delta_time) {
        logicalTick(delta_time);
        calculateFPS(delta_time);

        renderTick(delta_time);
    }

    void Engine::logicalTick(float delta_time) {
        g_runtime_global_context.m_window_system->tick();
    }

    void Engine::renderTick(float delta_time) {
        auto&& render_target = g_runtime_global_context.m_render_system->getRes("main");

        if (!render_target.has_value())
            LOG_FATAL("Forget to register `main` for m_render_system!!!");

        g_runtime_global_context.m_render_system->render(render_target.value());

        g_runtime_global_context.m_window_system->render(render_target.value());
    }

    void Engine::calculateFPS(float delta_time) {
        g_runtime_global_context.m_window_system->calFrameStats();
    }

    float Engine::calculateDeltaTime() {
        return g_runtime_global_context.m_window_system->calDeltaTime();
    }

} // namespace SRR