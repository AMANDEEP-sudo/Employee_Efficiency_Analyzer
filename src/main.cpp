#include <iostream>
#include <imgui.h>
#include "ImGuiManager.h"
#include "ImGuiAdmin.h"

using namespace std;

int main(int, char**)
{
    // Initialize ImGui Manager (handles GLFW, OpenGL, ImGui setup)
    ImGuiManager imgui_manager;
    
    if (!imgui_manager.initialize(1400, 900))
    {
        cerr << "Failed to initialize ImGui Manager!" << endl;
        return 1;
    }

    // Create ImGui Admin interface
    ImGuiAdmin imgui_admin;

    // Main loop
    while (!imgui_manager.shouldClose())
    {
        imgui_manager.beginFrame();

        // Render the admin interface
        imgui_admin.renderMainWindow();

        imgui_manager.endFrame();
    }

    // Cleanup
    imgui_manager.shutdown();

    return 0;
}
