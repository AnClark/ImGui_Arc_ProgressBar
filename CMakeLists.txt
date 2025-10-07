cmake_minimum_required (VERSION 3.20)

project (arc_progress_bar)

find_package (PkgConfig REQUIRED)


if (WIN32)
    set (OPENGL_LIBRARIES opengl32)
else ()
    pkg_check_modules(OPENGL REQUIRED gl)
endif ()


pkg_check_modules(GLFW REQUIRED glfw3)


set (IMGUI_DIR imgui/)
include_directories (
    .
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

add_executable (${PROJECT_NAME}
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp

    main.cpp
    arc_progress_bar.cpp
)

target_link_libraries (${PROJECT_NAME} PRIVATE
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${FFTW3_LIBRARIES}
)
