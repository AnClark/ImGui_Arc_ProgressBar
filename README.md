# Arc Progress Bar for Dear ImGui

A lightweight, customizable arc (circular) progress bar widget for [Dear ImGui](https://github.com/ocornut/imgui). This project provides an easy-to-use extension for rendering arc-shaped progress bars in your ImGui-based applications.

Here's how it looks like (see "**Build the Example Application**" below):

![Screenshot for example](screenshot.png)

## Features
- Draw arc/circular progress bars at any position or at the current ImGui cursor.
- Configurable arc angle, percentage, thickness, and color.
- Simple API and easy integration.

---

## Usage: `ImGuiExt::ProgressBarArc()`

### 1. Add to Your Project
- Copy `arc_progress_bar.cpp` and `arc_progress_bar.hpp` into your project.
- Make sure your project includes ImGui and its dependencies.
- Include the header in your code:
  
  ```cpp
  #include "arc_progress_bar.hpp"
  ```

- Make sure your project builds `arc_progress_bar.cpp` altogether.

### 2. API Reference

```cpp
namespace ImGuiExt {
    // Draw arc progress bar at a specific position
    void ProgressBarArc(float size, float max_angle_factor, float percentage, ImVec2 pos, float thickness = 2.0f);

    // Draw arc progress bar at current ImGui cursor position
    void ProgressBarArc(float size, float max_angle_factor, float percentage, float thickness = 2.0f);
}
```

- `size`: Diameter of the arc (in pixels)
- `max_angle_factor`: Arc's maximum angle factor (0~1, 1 for 360 degrees)
- `percentage`: Current progress percentage (0~1)
- `pos`: Position of the widget (top-left corner, in screen coordinates)
- `thickness`: Arc line thickness (default: 2.0f)


### 3. Example Usage

```cpp
// Draw at a specific position
ImGuiExt::ProgressBarArc(100, 1.0f, 0.75f, ImVec2(200, 200), 4.0f);

// Draw at current ImGui cursor position
ImGuiExt::ProgressBarArc(80, 0.8f, 0.5f, 3.0f);
```

---

### 4. Customizing Progress Bar Color

The arc progress bar uses ImGui's style colors for its appearance:
- The background arc uses `ImGuiCol_Button`.
- The progress (foreground) arc uses `ImGuiCol_ButtonActive`.

You can customize the color by pushing a new style color before drawing the widget:

```cpp
// Set a custom color for the progress arc
ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.5f, 0.2f, 1.0f));
ImGuiExt::ProgressBarArc(120, 1.0f, 0.6f, ImVec2(100, 100), 5.0f);
ImGui::PopStyleColor();

// Set a custom color for the background arc
ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 0.5f));
ImGuiExt::ProgressBarArc(120, 1.0f, 0.6f, ImVec2(100, 100), 5.0f);
ImGui::PopStyleColor();

// You can push both colors at once:
ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.7f, 0.1f, 1.0f));
ImGuiExt::ProgressBarArc(120, 1.0f, 0.6f, ImVec2(100, 100), 5.0f);
ImGui::PopStyleColor(2);
```

---

## Build the Example Application

This project includes a standalone example (`main.cpp`) using GLFW + OpenGL2 + ImGui.

### Prerequisites
- CMake >= 3.20
- OpenGL development libraries
- GLFW3

### Build Steps

```sh
mkdir build
cd build
cmake ..
make
./arc_progress_bar
```

---

## Source File Map

| File/Folder         | Description                                              |
|---------------------|---------------------------------------------------------|
| arc_progress_bar.hpp| Arc progress bar widget API declaration (header)        |
| arc_progress_bar.cpp| Arc progress bar widget implementation (source)         |
| main.cpp            | Example application using ImGui and the arc widget      |
| CMakeLists.txt      | CMake build script                                      |
| imgui/              | Dear ImGui source and backends                          |
| build/              | Build output directory (created after build)            |

---

## License

This project is licensed under the MIT License.

---

## Acknowledgements
- [Dear ImGui](https://github.com/ocornut/imgui) by Omar Cornut
