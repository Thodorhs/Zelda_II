#pragma once
#include "SDL.h"

typedef SDL_Surface BitmapSurface;
typedef SDL_Texture BitmapTexture;

typedef unsigned short Index;
typedef unsigned short Dim;

typedef unsigned char byte;
using GridIndex = byte;

#define MAX_WIDTH 21
#define MAX_HEIGHT 42
#define TILE_WIDTH 16
#define TILE_HEIGHT 16