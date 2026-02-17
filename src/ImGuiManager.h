#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class ImGuiManager
{
private:
    GLFWwindow* window;
    bool is_initialized;
    const char* glsl_version;

public:
    ImGuiManager();
    ~ImGuiManager();

    bool initialize(int window_width = 1400, int window_height = 900);
    void shutdown();
    bool shouldClose();
    void beginFrame();
    void endFrame();
    GLFWwindow* getWindow();
    bool isInitialized() { return is_initialized; }
};

#endif // IMGUI_MANAGER_H
