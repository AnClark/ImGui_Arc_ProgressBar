// Example code for arc progress bar widget for ImGui.
// Based on imgui/examples/example_glfw_opengl2/main.cpp.
//
// @author AnClark Liu (for this project), Omar Cornut (for Dear ImGui & origina example code)
// @date 2025-10-07

// Dear ImGui: standalone example application for GLFW + OpenGL2, using legacy fixed pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_glfw_opengl2/ folder**
// See imgui_impl_glfw.cpp for details.

#include "arc_progress_bar.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Arc Progress Bar Example By AnClark Liu", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Arc Progress Bar - Prototype");
            {
                ImDrawList *draw_list = ImGui::GetWindowDrawList();

                const ImColor col_stroke = ImColor(ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);  // Candidate: ImColor(ImVec4(1.0f, 1.0f, 0.4f, 1.0f));

                // This section shows how I came up with the arc drawing code.
                // I researched how to correctly manipulate the parameters of PathArcTo() function, especially a_min and a_max.
                //
                // The code is just for demonstration and debugging purpose.
                // You can skip reading this part if you are only interested in the final widget implementation.
                if (false)
                {
                    static float a_min_factor = -0.5f, a_max_factor = 1.0f;

                    ImGui::SliderFloat("a_min factor", &a_min_factor, -2.0f, 2.0f);
                    ImGui::SliderFloat("a_max factor", &a_max_factor, -2.0f, 2.0f);

                    ImVec2 pos = ImGui::GetCursorScreenPos(); // Get current insert point

                    float x = pos.x, y = pos.y;
                    constexpr float sz = 100.0f;
                    constexpr float th = 2.0f;

                    // Path
                    draw_list->PathArcTo(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, 3.141592f * a_min_factor, 3.141592f * a_max_factor);
                    draw_list->PathStroke(col_stroke, ImDrawFlags_None, th);
                }

                // This is the prototype code for arc progress bar.
                // It is NOT the final widget implementation.
                // You can skip reading this part if you are only interested in the final widget implementation.
                {
                    static int angle = 360;           // Progressbar arc angle (0 ~ 360 degree[s])
                    static int percentage = 100;    // Progressbar percentage
                    static float th = 2.0f;         // Thickness

                    ImGui::Text("Tune the parameters below to see how the arc is drawn:");
                    ImGui::SliderInt("Progressbar Angle", &angle, 0, 360);
                    ImGui::SliderInt("Percentage", &percentage, 0, 100);
                    ImGui::SliderFloat("Thickness", &th, 1.00f, 10.0f);

                    ImVec2 pos = ImGui::GetCursorScreenPos(); // Get current insert point

                    float x = pos.x, y = pos.y;    // Position
                    constexpr float sz = 100.0f;        // Size (aka. Diameter)

                    ImGui::Dummy(ImVec2(sz, sz));   // Placeholder

                    constexpr float ONE_DIV_360f = 1.0f / 360.0f;   // Performance tweak

                    float a_min_factor, a_max_factor, a_max_factor_100percentage;
                    a_min_factor = -1.5f + ((360 - angle) * ONE_DIV_360f);    // Angle PI*-1.5f resides in the bottom point of circle
                    a_max_factor_100percentage = (a_min_factor + 1.0f) * -1.0f;       // Arc max factor on 100% percentage state

                    float a_factor_delta = (a_max_factor_100percentage - a_min_factor) * (percentage * 0.01f);
                    a_max_factor = a_min_factor + a_factor_delta;

                    // Path
                    draw_list->PathArcTo(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, 3.141592f * a_min_factor, 3.141592f * a_max_factor);
                    draw_list->PathStroke(col_stroke, ImDrawFlags_None, th);

                    ImGui::Text("a_min_factor = %f, a_max_factor = %f", a_min_factor, a_max_factor);
                }


            }

            ImGui::End();

            // This window shows how to use the final arc progress bar widget.
            ImGui::Begin("Arc Progressbar - Widget Implementation");
            {
                static int angle = 360;         // Progressbar arc angle (0 ~ 360 degree[s])
                static int percentage = 100;    // Progressbar percentage
                static float th = 4.0f;         // Thickness

                ImGui::Text("Tune the parameters below to see how the arc is drawn:");
                ImGui::SliderInt("Progressbar Angle", &angle, 0, 360);
                ImGui::SliderInt("Percentage", &percentage, 0, 100);
                ImGui::SliderFloat("Thickness", &th, 1.00f, 10.0f);

                // Draw 5 progress bars in ImGui-managed positions, in different sizes.
                ImGui::Text("Progress bars in different sizes, with a special yellowish one:");
                for (auto item = 1; item <= 5; item++)
                {
                    ImGuiExt::ProgressBarArc(item * 40, angle, percentage, th);
                    ImGui::SameLine(0, 20);
                }

                // Draw progress bar in absolute position, with custom yellowish color.
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 0.4f, 0.5f));
                ImGuiExt::ProgressBarArc(200, angle, percentage, ImVec2(200, 200), th);
                ImGui::PopStyleColor();
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
        // you may need to backup/reset/restore other state, e.g. for current shader using the commented lines below.
        //GLint last_program;
        //glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        //glUseProgram(0);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        //glUseProgram(last_program);

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
