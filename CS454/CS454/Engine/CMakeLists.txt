# CMakeList.txt : CMake project for Zelda, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#Add source to this project's executable.


add_executable(Zelda_II  "Src/main.cpp" "Src/GameLoop.cpp"  "Src/ZeldaApp.cpp"  "Src/MapEditor.cpp" "Src/ViewWindow.cpp" "Include/GridMotion.h" "Include/Grid.h" )

target_link_libraries(Zelda_II  SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Zelda_II  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.