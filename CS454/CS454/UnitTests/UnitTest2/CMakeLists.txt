# CMakeList.txt : CMake project for Zelda, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#Add source to this project's executable.


add_executable(UnitTest2  "../../Engine/Src/main.cpp" "../../Engine/Src/GameLoop.cpp" "Src/UnitTest2App.cpp" "Src/GridCompute.cpp" "../../Engine/Src/MapEditor.cpp" "../../Engine/Src/ViewWindow.cpp"  "Src/GridMotion.cpp")

target_link_libraries(UnitTest2  SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UnitTest2  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.