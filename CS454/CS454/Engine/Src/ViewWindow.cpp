#include "../../Engine/Include/ViewWindow.h"
#include "../../Engine/Include/Util/ConfigFuncs.h";

Point viewPosCached{ -1, -1 };
SDL_Rect PTsrcrect;
SDL_Rect PTdstrect;


Dim dpyX = 0, dpyY = 0;

void pre_cache(void) {
	for (unsigned short i = 0; i < 255; ++i)
		div_index[i] = i / 12,mod_index[i] = i % 12;
}


void PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture) {
	if (tile == 0xffff)
		return;
	PTsrcrect.x = MUL_TILE_WIDTH(mod_index[tile],Engine_Consts.power);
	PTsrcrect.y = MUL_TILE_HEIGHT(div_index[tile],Engine_Consts.power);
	

	PTsrcrect.h = PTsrcrect.w = 16;

	PTdstrect.x = x-dpyX;
	PTdstrect.y = y-dpyY;
	PTdstrect.h = PTdstrect.w = 16;
	SDL_RenderCopy(myrenderer, texture, &PTsrcrect, &PTdstrect); //Same as SDL_BlitSurface but uses the gpu so its faster
}


void TileTerrainDisplay(TileMap* map, const SDL_Rect& viewWin, const SDL_Rect& displayArea, SDL_Renderer* myrenderer, SDL_Texture* Tileset, SDL_Texture* RenderTextureTarget) {
	Dim power = Engine_Consts.power;

	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = DIV_TILE_WIDTH(viewWin.x,power);
		auto startRow = DIV_TILE_HEIGHT(viewWin.y,power);
		auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1,power);
		auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1,power);
		dpyX = MOD_TILE_WIDTH(viewWin.x,Engine_Consts.Tile_width);
		dpyY = MOD_TILE_WIDTH(viewWin.y,Engine_Consts.Tile_height);
		
		viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;

		SDL_SetRenderTarget(myrenderer, RenderTextureTarget); //Setting the target of SDL_RenderCopy to be the texture

		for (unsigned short row = startRow; row <= endRow; ++row)
			for (unsigned short col = startCol; col <= endCol; ++col)
				PutTile(MUL_TILE_WIDTH(col - startCol,Engine_Consts.power), MUL_TILE_HEIGHT(row - startRow,Engine_Consts.power), (*map)[row][col], myrenderer, Tileset);

		SDL_SetRenderTarget(myrenderer, NULL); //Unsetting the target of SDL_RenderCopy (now the target is the screen render)
	}
	int scale = get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_global");
	PTdstrect.x = 0;
	PTdstrect.y = 0;
	PTdstrect.h = viewWin.h*scale;
	PTdstrect.w = viewWin.w*scale;//scaled //GWINDOW
	SDL_RenderCopy(myrenderer, RenderTextureTarget, NULL, &PTdstrect); //Setting the texture we loaded earlier(Rendertexture) to be displayed on our window
	//SDL_RenderCopy(myrenderer, RenderTextureTarget, NULL, NULL); //Setting the texture we loaded earlier(Rendertexture) to be displayed on our window
}



int GetMapPixelWidth()
{
	return Engine_Consts.Map_width ;
}

int GetMapPixelHeight()
{
	return Engine_Consts.Map_height;
}

void Scroll(SDL_Rect* viewWin, int dx, int dy)
{
	viewWin->x += dx; viewWin->y += dy;
}

bool CanScrollHoriz(const SDL_Rect& viewWin, int dx)
{
	return viewWin.x >= -dx && (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}

bool CanScrollVert(const SDL_Rect& viewWin, int dy)
{
	return viewWin.y >= -dy && (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}

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
