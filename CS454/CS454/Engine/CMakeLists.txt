# CMakeList.txt : CMake project for Zelda, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#Add source to this project's executable.


include_directories("Src/MapEditor.cpp" "Src/GameLoop.cpp" "Include/App.h" "Include/MapEditor.h" "Src/ZeldaApp.cpp" "Include/ZeldaApp.h" "Src/ViewWindow.cpp" "Include/ViewWindow.h")
add_executable(Zelda_II "Src/MapEditor.cpp" "Src/main.cpp" "Src/GameLoop.cpp" "Include/App.h" "Include/MapEditor.h" "Src/ZeldaApp.cpp" "Include/ZeldaApp.h" "Src/ViewWindow.cpp" "Include/ViewWindow.h" "Include/GridCompute.h" "Src/GridCompute.cpp" "Include/GridMotion.h" "Src/GridMotion.cpp")

target_link_libraries(Zelda_II  SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Zelda_II  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.