# CMakeList.txt : CMake project for Zelda, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
#Add source to this project's executable.
set(SDL2_TTF_INCLUDE_DIR "../../${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf-2.22.0/include")

add_executable(UnitTest3     
"Src/UnitTest3App.cpp"  
"../../Engine/Src/main.cpp"
"../../Engine/Src/GameLoop.cpp"  
"../../Engine/Src/MapEditor.cpp" 
"../../Engine/Src/ViewWindow.cpp" 
"../../Engine/Src/Parsefuncs.cpp" 
"../../Engine/Src/ConfigFuncs.cpp"
"../../Engine/Src/Grid.cpp"
"../../Engine/Src/TileLayer.cpp"
"../../Engine/Src/GridMotion.cpp"
"../../Engine/Src/FilmParser.cpp"
"../../Engine/Src/DestructionManager/DestructionManager.cpp"
"../../Engine/Src/AnimationFilmHolder.cpp" 
"Src/initAnimationsSprites.cpp"
"Src/init_sprites/init_elevators.cpp"
"Src/init_sprites/init_doors.cpp"
"Src/init_sprites/init_guma.cpp"
"Src/init_sprites/init_guma_proj.cpp"
"Src/init_sprites/init_link.cpp"
"../../Engine/Src/Sprites/Sprite.cpp"
"../../Engine/Src/Sprites/Clipper.cpp"
"../../Engine/Src/Sprites/MotionQuantizer.cpp"
"../../Engine/Src/Sprites/SpriteHelpers.cpp"
"../../Engine/Src/Animators/Animator.cpp"
"../../Engine/Src/Animators/FrameRangeAnimator.cpp"
"../../Engine/Src/Animators/AnimatorManager.cpp"
"../../Engine/Src/SystemClock/SystemClock.cpp"
"../../Engine/Src/Sprites/GravityHandler.cpp"
"../../Engine/Src/Animators/MovingAnimator.cpp"
"../../Engine/Src/Animators/ScrollAnimator.cpp"
"../../Engine/src/Input.cpp"
"../../Engine/src/Sprites/CollisionChecker.cpp"
"Src/SpriteHandling/SpriteHandlers.cpp"
"Src/StatPrinting/StatPrinting.cpp"
"Src/init_sprites/init_bot.cpp"
"Src/Characters/initCharacters.cpp"
"Include/Characters/Guma.h"
"Src/Characters/Character.cpp"
"Src/AI/AI.cpp"
 "Src/init_sprites/init_staflos.cpp"
 "Src/init_sprites/init_wosu.cpp"
 "Include/Characters/PalaceBot.h"
 "Include/Characters/Staflos.h"
 "Include/Characters/Wosu.h"
"../../Engine/Src/Animators/MovingPathAnimator.cpp"
"Src/CreateSprite.cpp" "Src/SoundManager/SoundManager.cpp")

target_link_libraries(UnitTest3  SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UnitTest3  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.