#pragma once

#include <Windows.h>
#include <filesystem>
#include <string>

#include <core/base/timer.h>

namespace SRR::Util {
    class TGAImage;
}

namespace SRR {
    struct WindowCreateInfo {
        int         width{1280};
        int         height{720};
        std::string title{};
        std::string path{};
    };

    class WindowSystem {
    public:
        WindowSystem();
        ~WindowSystem();
        WindowSystem(const WindowSystem&)            = delete;
        WindowSystem& operator=(const WindowSystem&) = delete;

        void  init(const WindowCreateInfo& create_info);
        void  render(Util::TGAImage*);
        void  tick();
        void  resetTimer();
        void  calFrameStats();
        float calDeltaTime();

        void outputRes(Util::TGAImage*);
        int  getWidth() const;
        int  getHeight() const;

        bool isShouldClose();

        LRESULT CALLBACK msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        std::filesystem::path m_root_path;
        Util::Timer           m_timer;
    };
} // namespace SRR