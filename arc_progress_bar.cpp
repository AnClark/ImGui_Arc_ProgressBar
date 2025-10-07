#include "arc_progress_bar.hpp"

/**
 * @brief Get color from ImGui style safely.
 *
 * @param color_id ImGui color ID.
 * @return ImColor Return the color, or default color if invalid ID.
 */
static inline ImColor _GetStyleColor(const ImGuiCol_ color_id)
{
    IM_ASSERT(color_id >= 0 && color_id < ImGuiCol_COUNT);

    if (color_id < 0 || color_id >= ImGuiCol_COUNT)
        return ImColor(DEFAULT_FOREGROUND_COLOR);    // Fallback

    return ImColor(ImGui::GetStyle().Colors[color_id]);
}

/**
 * @brief The actual drawing function for arc progress bar.
 *
 * @param size Diameter of the arc.
 * @param max_angle_factor Arc's maximum angle factor (0~1, 1 for 360 degrees).
 * @param percentage Current progress percentage (0~1).
 * @param thickness Arc line thickness.
 * @param pos Position of the widget (top-left corner).
 */
void _DrawArc(float size, float max_angle_factor, float percentage, float thickness, ImVec2 pos)
{
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    float x = pos.x, y = pos.y;    // Position

    constexpr float ONE_DIV_360f = 1.0f / 360.0f;   // Performance tweak

    float a_min_factor, a_max_factor, a_max_factor_100percentage;
    a_min_factor = -1.5f + ((360 - max_angle_factor) * ONE_DIV_360f);    // Angle PI*-1.5f resides in the bottom point of circle
    a_max_factor_100percentage = (a_min_factor + 1.0f) * -1.0f;       // Arc max factor on 100% percentage state

    float a_factor_delta = (a_max_factor_100percentage - a_min_factor) * (percentage * 0.01f);
    a_max_factor = a_min_factor + a_factor_delta;

    // Path
    draw_list->PathArcTo(ImVec2(x + size * 0.5f, y + size * 0.5f), size * 0.5f, 3.141592f * a_min_factor, 3.141592f * a_max_factor);
    draw_list->PathStroke(_GetStyleColor(ImGuiCol_ButtonActive), ImDrawFlags_None, thickness);
}

void ImGuiExt::ProgressBarArc(float size, float max_angle_factor, float percentage, ImVec2 pos, float thickness)
{
    // By default, ImDrawList draws in absolute position relaitve to the canvas, NOT the window.
    // So we need to consider the window position if we want to draw something inside the window.

    ImVec2 window_pos = ImGui::GetWindowPos();    // Do not forget to get window's position.

    // And do not forget to add the window position to our own position.
    _DrawArc(size, max_angle_factor, percentage, thickness, ImVec2(pos.x + window_pos.x, pos.y + window_pos.y));
}

void ImGuiExt::ProgressBarArc(float size, float max_angle_factor, float percentage, float thickness)
{
    ImVec2 pos = ImGui::GetCursorScreenPos(); // Get current insert point
    ImGui::Dummy(ImVec2(size, size));   // Placeholder

    _DrawArc(size, max_angle_factor, percentage, thickness, pos);
}
