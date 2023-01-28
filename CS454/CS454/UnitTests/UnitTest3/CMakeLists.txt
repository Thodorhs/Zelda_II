# CMakeList.txt : CMake project for Zelda, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#Add source to this project's executable.


add_executable(UnitTest3  "../../Engine/Src/main.cpp" "../../Engine/Src/GameLoop.cpp"   "../../Engine/Src/GridCompute.cpp" "../../Engine/Src/GridUtil.cpp" "../../Engine/Src/MapEditor.cpp" "../../Engine/Src/ViewWindow.cpp"  "../../Engine/Src/GridMotion.cpp" "../../Engine/Src/GridUtil.cpp" "Src/GridLayer.cpp" "Src/TileLayer.cpp" "Src/AnimationFilmHolder.cpp" "Src/AnimatorSrc/Animator.cpp" "Src/AnimatorSrc/MovingAnimator.cpp" "Src/AnimatorSrc/FrameRangeAnimator.cpp"  "Src/SystemClock.cpp" "Src/AnimatorSrc/TickAnimator.cpp" "Src/FilmParser.cpp" "Src/Sprites/MotionQuantizer.cpp" "Src/Sprites/Sprite.cpp" "Src/Sprites/GravityHandler.cpp" "Src/Sprites/CollisionChecker.cpp"  "Src/Sprites/Clipper.cpp"   "Src/SpriteManager.cpp"  "Src/GameLoopFuncs/Input.cpp" "Src/Link_test/GameCharacters.h"  "Src/Link_test/GreatPalaceBot.h" "Src/Link_test/GameCharacters.cpp" "Src/Initialise_characters.h" "Src/Initialise_characters.cpp" "Src/UnitTest3App.cpp" "Src/Link_test/Guma.h" "Src/InitPalacebot.cpp" "Src/InitGuma.cpp" "Src/AnimatorSrc/ScrollingAnimator.cpp" "Src/Recycler/Recycler.h" "Src/Link_test/Wosu.h" "Src/InitWosu.cpp" "Src/Sprites/CombatSystem.cpp") 

target_link_libraries(UnitTest3  SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UnitTest3  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.