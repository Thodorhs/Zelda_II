#pragma once
#include "SDL.h"
#include "../../../../Engine/Include/TileLayer.h"
#define FONT_SIZE 15
void render_stats(SDL_Renderer* renderer, TileLayer* layer);
bool init_ttf();