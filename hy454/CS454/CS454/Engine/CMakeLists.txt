cmake_minimum_required (VERSION 3.8)

# CMakeList.txt : CMake project for Test69, include source and define
# project specific logic here.
#


#Add source to this project's executable.
include_directories("src/Editor.cpp" "src/main.cpp" "src/GameLoop.cpp" "include/App.h" "include/Editor.h" "src/ZeldaApp.cpp" "include/ZeldaApp.h")
add_executable (peos  "src/main.cpp" "src/GameLoop.cpp" "include/App.h" "include/Editor.h" "src/ZeldaApp.cpp" "include/ZeldaApp.h")
install(TARGETS peos DESTINATION bin)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET peos PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
