# CMakeList.txt : CMake project for Zelda, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#Add source to this project's executable.


add_executable(Zelda_II  "Src/main.cpp" "Src/GameLoop.cpp"     "Src/MapEditor.cpp" "Src/ViewWindow.cpp" "Include/Grid/GridMotion.h" "Include/Grid/Grid.h"  "Include/AnimationFilmHolder.h/" "Include/Util/EngineDefines.h" "Include/KeyFrameAnimation/AnimationFilmHolder.h" "Include/KeyFrameAnimation/BitmapLoader.h" "Include/Animations/MovingAnimation.h" "Include/Animations/MovingPathAnimation.h" "Include/Animations/FlashAnimation.h" "Include/Animations/ScrollAnimation.h" "Include/Animators/Animator.h" "Include/Animators/MovingAnimator.h" "Include/Animators/FrameRangeAnimator.h" "Include/Animators/AnimatorManager.h" "Include/Util/SystemClock.h" "Include/Animations/TickAnimation.h" "Include/Animators/TickAnimator.h" "Include/KeyFrameAnimation/FilmParser.h" "Include/Sprites/Sprite.h" "Include/Sprites/MotionQuantizer.h" "Include/Sprites/GravityHandler.h" "Include/Sprites/CollisionChecker.h" "Include/Sprites/Clipper.h" "Include/Sprites/SpriteManager.h" "Include/GameLoopFuncs/Input.h" "Include/Sprites/BoundingArea.h" "Include/Animators/ScrollingAnimator.h" "Include/Util/Configurator.h" "Include/Util/Config_Factory.h" "Include/Util/ConfiguratorManager.h" "Src/Parsefuncs.cpp" "Include/Util/ParseFuncs.h" "Include/Util/ConfigFuncs.h" "Src/ConfigFuncs.cpp" "Src/Grid.cpp" "Include/Util/Print.h" "Src/AnimationFilmHolder.cpp" "Src/FilmParser.cpp" "Src/Animators/FrameRangeAnimator.cpp" "Src/Animators/AnimatorManager.cpp" "Src/Sprites/Sprite.cpp" "Src/Sprites/MotionQuantizer.cpp" "Src/Sprites/Clipper.cpp"  "Include/Sprites/SpriteHelpers.h" "Src/Sprites/SpriteHelpers.cpp" "Src/Animators/Animator.cpp" "Src/SystemClock/SystemClock.cpp" "Src/Sprites/GravityHandler.cpp" "Src/Animators/MovingAnimator.cpp" "Src/Animators/ScrollAnimator.cpp")

target_link_libraries(Zelda_II  SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Zelda_II  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.