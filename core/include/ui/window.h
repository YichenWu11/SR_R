#pragma once

#include <string>

struct GLFWwindow;

namespace SRR {
class Window {
public:
    Window(int res_x, int res_y, const std::string& n);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void run();
    void processInput();

private:
    std::string m_name;
    GLFWwindow* m_p2window;
};
} // namespace SRR