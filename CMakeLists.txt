cmake_minimum_required(VERSION 3.10)
project(prog)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Подкаталог для ImGui
add_subdirectory(lib/imgui)

# Путь к папке с заголовочными файлами
include_directories(include)

set(SOURCES
    src/main.cpp
    src/model/GameLogic.cpp
    src/model/Model.cpp
    src/presenter/Presenter.cpp
    src/view/GameWindow.cpp
    src/view/SettingsWindow.cpp
    src/view/View.cpp
	src/view/ImGuiTheme.cpp
)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

message(STATUS "OpenGL Libraries: ${OPENGL_LIBRARIES}")



# Исполняемый файл
add_executable(prog ${SOURCES})



# Исполняемый файл с библиотекой ImGui
target_link_libraries(prog 
	imgui 
	glfw 
	${OPENGL_LIBRARIES} 
	SDL2::SDL2 
	SDL2_image::SDL2_image
)

# Копирование папки assets в директорию сборки
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
