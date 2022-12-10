#pragma once

#include <Windows.h>

#include <glm/glm.hpp>

namespace SRR::Util {
    class TGAImage;
}

typedef struct mouse {
    // for camera orbit
    glm::vec2 orbit_pos;
    glm::vec2 orbit_delta;
    // for first-person view (diabled now)
    glm::vec2 fv_pos;
    glm::vec2 fv_delta;
    // for mouse wheel
    float wheel_delta;
} mouse_t;

typedef struct window {
    HWND h_window;
    HDC mem_dc;
    HBITMAP bm_old;
    HBITMAP bm_dib;
    unsigned char* window_fb;
    int width;
    int height;
    char keys[512];
    char buttons[2]; // left button: 0; right button: 1
    int is_close;
    mouse_t mouse_info;
} window_t;

extern window_t* window;

int window_init(int width, int height, const char* title, WNDPROC func);
int window_destroy();
void window_draw(SRR::Util::TGAImage* framebuffer);
void msg_dispatch();
glm::vec2 get_mouse_pos();
float platform_get_time(void);

// ************************************************************************

// std::wstring string2wstring(const std::string& str) {
//     std::wstring result;
//     int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
//     TCHAR* buffer = new TCHAR[len + 1];
//     MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
//     buffer[len] = '\0';
//     result.append(buffer);
//     delete[] buffer;
//     return result;
// }

// std::string wstring2string(const std::wstring& wstr) {
//     std::string result;
//     int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
//     char* buffer = new char[len + 1];
//     WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
//     buffer[len] = '\0';
//     result.append(buffer);
//     delete[] buffer;
//     return result;
// }
