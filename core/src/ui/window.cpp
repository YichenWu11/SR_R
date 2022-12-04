#include <cassert>

#include <glfw/glfw3.h>

#include <ui/window.h>

using namespace SRR;

Window::Window(int res_x, int res_y, const std::string& n) :
    m_name(n) {
    glfwInit();
    m_p2window = glfwCreateWindow(res_x, res_y, n.c_str(), NULL, NULL);
    assert(m_p2window != nullptr && "Failed to create GLFW window");
    glfwMakeContextCurrent(m_p2window);
}

Window::~Window() {
    glfwDestroyWindow(m_p2window);
}

void Window::processInput() {
}

void Window::run() {
    while (!glfwWindowShouldClose(m_p2window)) {
        processInput();

        glfwSwapBuffers(m_p2window);
        glfwPollEvents();
    }
}
