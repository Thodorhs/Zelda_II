#pragma once
#include "../Grid/GridLayer.h"
#include "../TileLayer.h"
#include "SDL.h"

void myInput(TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& is_running, bool& mouse_down);