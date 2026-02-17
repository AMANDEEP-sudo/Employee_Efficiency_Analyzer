#include "ImGuiManager.h"
#include <iostream>

ImGuiManager::ImGuiManager() : window(nullptr), is_initialized(false)
{
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    glsl_version = "#version 100";
#elif defined(__APPLE__)
    glsl_version = "#version 150";
#else
    glsl_version = "#version 130";
#endif
}

ImGuiManager::~ImGuiManager()
{
    shutdown();
}

bool ImGuiManager::initialize(int window_width, int window_height)
{
    // Setup window
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    });

    if (!glfwInit())
        return false;

    // GL 3.0 + GLSL 130
    const char* glsl_version_local = "#version 130";
#ifdef __APPLE__
    glsl_version_local = "#version 150";
#endif

    // Create window with graphics context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(window_width, window_height, "Employee Efficiency Tracker - Modern UI", NULL, NULL);
    if (window == NULL)
        return false;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular windows.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version_local);

    is_initialized = true;
    return true;
}

void ImGuiManager::shutdown()
{
    if (is_initialized)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (window)
        {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
        is_initialized = false;
    }
}

bool ImGuiManager::shouldClose()
{
    return window && glfwWindowShouldClose(window);
}

void ImGuiManager::beginFrame()
{
    // Poll and handle events
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::endFrame()
{
    ImGuiIO& io = ImGui::GetIO();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
}

GLFWwindow* ImGuiManager::getWindow()
{
    return window;
}
