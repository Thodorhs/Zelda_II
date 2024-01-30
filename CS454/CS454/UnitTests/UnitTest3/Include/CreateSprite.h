#pragma once
#include "../../../Engine/Include/Sprites/Sprite.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"

void drop_point_action(Sprite* s1, Sprite* s2);
void drop_big_point_action(Sprite* s1, Sprite* s2);
void drop_blue_pot_action(Sprite* s1, Sprite* s2);
void drop_red_pot_action(Sprite* s1, Sprite* s2);
Sprite* create_drop_sprite(Sprite* s, AnimationFilmHolder& holder, std::string film, int* x, TileLayer* layer);
   
