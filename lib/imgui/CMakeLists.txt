set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

# Пути к заголовочным файлам
target_include_directories(imgui PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/imgui
	${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)
