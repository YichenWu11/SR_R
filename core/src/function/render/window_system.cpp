#include <cassert>
#include <chrono>

#include <glm/gtc/random.hpp>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>

#include <core/base/macro.h>
#include <core/base/tgaimage.h>
#include <function/global/global_context.h>
#include <function/render/window_system.h>
#include <platform/win32.h>

using namespace std::chrono;

namespace SRR {
    // ************************************************************************************
    // Message Process

    static LRESULT CALLBACK mainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        return g_runtime_global_context.m_window_system->msgProc(hwnd, msg, wParam, lParam);
    }

    // TODO: Input Process Here
    LRESULT CALLBACK WindowSystem::msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_ACTIVATE:
                if (LOWORD(wParam) == WA_INACTIVE) {
                    m_timer.Stop();
                }
                else {
                    m_timer.Start();
                }
                return 0;
            case WM_ENTERSIZEMOVE:
                m_timer.Stop();
                return 0;
            case WM_EXITSIZEMOVE:
                m_timer.Start();
                return 0;
            case WM_CLOSE:
                window->is_close = 1;
                break;
            case WM_KEYDOWN:
                window->keys[wParam & 511] = 1;
                break;
            case WM_KEYUP:
                window->keys[wParam & 511] = 0;
                break;
            case WM_LBUTTONDOWN:
                window->mouse_info.orbit_pos = get_mouse_pos();
                window->buttons[0]           = 1;
                break;
            case WM_LBUTTONUP:
                window->buttons[0] = 0;
                break;
            case WM_RBUTTONDOWN:
                window->mouse_info.fv_pos = get_mouse_pos();
                window->buttons[1]        = 1;
                break;
            case WM_RBUTTONUP:
                window->buttons[1] = 0;
                break;
            case WM_MOUSEWHEEL:
                window->mouse_info.wheel_delta = GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
                break;

            default: return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }
    // ************************************************************************************

    // ************************************************************************************

    WindowSystem::WindowSystem() {
    }

    WindowSystem::~WindowSystem() {
        window_destroy();
    }

    void WindowSystem::init(const WindowCreateInfo& create_info) {
        m_root_path = create_info.path;
        window_init(create_info.width, create_info.height, create_info.title.c_str(), mainMsgProc);
    }

    bool WindowSystem::isShouldClose() {
        return window->is_close;
    }

    void WindowSystem::resetTimer() {
        m_timer.Reset();
    }

    void WindowSystem::tick() {
        m_timer.Tick();
    }

    int WindowSystem::getWidth() const {
        return window->width;
    }

    int WindowSystem::getHeight() const {
        return window->height;
    }

    void WindowSystem::render(Util::TGAImage* target) {
        target->flip_vertically();
        window_draw(target);
        target->flip_vertically();
        msg_dispatch();
    }

    void WindowSystem::calFrameStats() {
        static int   frameCnt    = 0;
        static float timeElapsed = 0.0f;

        frameCnt++;

        // Compute averages over one second period.
        if ((m_timer.TotalTime() - timeElapsed) >= 1.0f) {
            float fps = (float)frameCnt; // fps = frameCnt / 1
            // float mspf = 1000.0f / fps;

            // std::string fpsStr = std::to_string(fps);
            // std::string mspfStr = std::to_string(mspf);

            LOG_INFO("fps : {}", fps);

            // Reset for next average.
            frameCnt = 0;
            timeElapsed += 1.0f;
        }
    }

    float WindowSystem::calDeltaTime() {
        return m_timer.DeltaTime();
    }

    void WindowSystem::outputRes(Util::TGAImage* target) {
        target->flip_vertically();
        target->write_tga_file(std::filesystem::path(m_root_path / "assets/res/output.tga").string().c_str());
        target->flip_vertically();
    }

} // namespace SRR
