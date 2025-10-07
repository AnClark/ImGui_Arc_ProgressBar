/**
 * @file arc_progress_bar.hpp
 * @brief Provide a arc progress bar widget for ImGui.
 *
 * @author AnClark Liu
 * @date 2025-10-07
 * @license MIT
 */

#pragma once

#include <imgui.h>

/**
 * @brief Default foreground color (yellowish).
 */
const ImColor DEFAULT_FOREGROUND_COLOR = ImColor(ImVec4(1.0f, 1.0f, 0.4f, 1.0f));

/**
 * @namespace ImGuiExt
 * @brief ImGui's extension namespace. Using this instead of polluting ImGui's own namespace.
 */
namespace ImGuiExt
{

    /**
     * @brief Draw a arc progress bar at specified position.
     * @param size Diameter of the arc.
     * @param max_angle_factor Arc's maximum angle factor (0~1, 1 for 360 degrees).
     * @param percentage Current progress percentage (0~1).
     * @param pos Position of the widget (top-left corner).
     * @param thickness Arc line thickness, default is 2.0f.
     */
    void ProgressBarArc(float size, float max_angle_factor, float percentage, ImVec2 pos, float thickness = 2.0f);

    /**
     * @brief Draw a arc progress bar at current ImGui cursor position.
     * @param size Arc diameter.
     * @param max_angle_factor Arc maximum angle factor (0~1, 1 for 360 degrees).
     * @param percentage Percentage of progress (0~1).
     * @param thickness Arc line thickness, default is 2.0f.
     */
    void ProgressBarArc(float size, float max_angle_factor, float percentage, float thickness = 2.0f);
}
