#pragma once
#include "../Sprites/Sprite.h"
#include "../Grid/GridLayer.h"
#include "../TileLayer.h"
#include "SDL.h"
#include "../../../UnitTests/UnitTest3/Src/Link_test/Link.h"

void walk_left(MovingAnimation* animation, FrameRangeAnimation* f_animation, FrameRangeAnimator* f_animator, MovingAnimator* m_animator, int dx, int dy);
void walk_right(MovingAnimation* animation, FrameRangeAnimation* f_animation, FrameRangeAnimator* f_animator, MovingAnimator* m_animator, int dx, int dy);
void myInput(Sprite* Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& is_running, bool& mouse_down,Link_Class& link);