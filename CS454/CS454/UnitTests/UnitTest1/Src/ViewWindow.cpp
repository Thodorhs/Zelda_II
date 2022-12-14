#include "../../../Engine/Include/ViewWindow.h"

SDL_Texture* RenderTextureTarget;
Point viewPosCached{ -1, -1 };
SDL_Rect PTsrcrect;
SDL_Rect PTdstrect;

void PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture) {
	PTsrcrect.x = MUL_TILE_WIDTH(tile % 12);
	PTsrcrect.y = MUL_TILE_HEIGHT(tile / 12);
	PTsrcrect.h = PTsrcrect.w = 16;

	PTdstrect.x = x;
	PTdstrect.y = y;
	PTdstrect.h = PTdstrect.w = 16;
	SDL_RenderCopy(myrenderer, texture, &PTsrcrect, &PTdstrect); //Same as SDL_BlitSurface but uses the gpu so its faster
}


void TileTerrainDisplay(TileMap* map, const SDL_Rect& viewWin, const SDL_Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer) {
	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = DIV_TILE_WIDTH(viewWin.x);
		auto startRow = DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);

		viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;

		SDL_Texture* Tileset = SDL_CreateTextureFromSurface(myrenderer, ImgSurface); //Loading the tileset
		RenderTextureTarget = SDL_CreateTexture(myrenderer, 0, SDL_TEXTUREACCESS_TARGET, viewWin.w, viewWin.h); //Preparing to load the map to the texture
		SDL_SetRenderTarget(myrenderer, RenderTextureTarget); //Setting the target of SDL_RenderCopy to be the texture

		for (unsigned short row = startRow; row <= endRow; ++row)
			for (unsigned short col = startCol; col <= endCol; ++col) 
				PutTile(MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), (*map)[row][col], myrenderer, Tileset);
		
		SDL_SetRenderTarget(myrenderer, NULL); //Unsetting the target of SDL_RenderCopy (now the target is the screen render)
	}

	PTdstrect.x = 0;
	PTdstrect.y = 0;
	PTdstrect.h = 240;
	PTdstrect.w = 320;
	SDL_RenderCopy(myrenderer, RenderTextureTarget, NULL, &PTdstrect); //Setting the texture we loaded earlier(Rendertexture) to be displayed on our window

	//SDL_RenderCopy(myrenderer, RenderTextureTarget, NULL, NULL); //Setting the texture we loaded earlier(Rendertexture) to be displayed on our window
}


int GetMapPixelWidth() 
{ return 336; }

int GetMapPixelHeight() 
{ return 672; }

void Scroll(SDL_Rect* viewWin, int dx, int dy)
{viewWin->x += dx; viewWin->y += dy;}

bool CanScrollHoriz(const SDL_Rect& viewWin, int dx)
{return viewWin.x >= -dx && (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();}

bool CanScrollVert(const SDL_Rect& viewWin, int dy)
{ return viewWin.y >= -dy && (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();}

void FilterScrollDistance(
	int viewStartCoord, // x or y
	int viewSize, // w or h
	int* d, // dx or dy
	int maxMapSize // w or h 
) {
	auto val = *d + viewStartCoord;
	if (val < 0)
		*d = viewStartCoord; // cross low bound
	else
		if (viewSize >= maxMapSize)// fits entirely
			*d = 0;
		else
			if ((val + viewSize) >= maxMapSize) // cross upper bound
				*d = maxMapSize - (viewStartCoord + viewSize);
}

void FilterScroll(const SDL_Rect& viewWin, int* dx, int* dy) {
	FilterScrollDistance(viewWin.x, viewWin.w, dx, GetMapPixelWidth());
	FilterScrollDistance(viewWin.y, viewWin.h, dy, GetMapPixelHeight());
}

void ScrollWithBoundsCheck(SDL_Rect* viewWin, int dx, int dy) {
	FilterScroll(*viewWin, &dx, &dy);
	Scroll(viewWin, dx, dy);
}
