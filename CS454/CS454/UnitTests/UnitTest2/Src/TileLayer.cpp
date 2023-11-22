#include <utility>

#include "../../../Engine/Include/TileLayer.h"

TileLayer::TileLayer(ViewWindow_t _ViewWin,SDL_Texture* _dpybuffer,TileMap* _map,std::string _id,Dim _scale) {
	assert(_map);
	auto swallow_Copy(*_map); //we don't want a pointer, the global tile map will change to contain other layers
	map = swallow_Copy; //assign the swallow copy
	id = std::move(_id);
	viewWin = _ViewWin;
	scale = _scale;
	dpybuffer = _dpybuffer;
	pre_cache();
}



SDL_Texture* TileLayer::get_bitmap() {
	return dpybuffer;
}


void TileLayer::PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture) {
	
	ViewWindow_t PTsrcrect{};
	ViewWindow_t PTdstrect{};
	PTsrcrect.x = MUL_TILE_WIDTH(mod_index[tile], Engine_Consts.power);
	PTsrcrect.y = MUL_TILE_HEIGHT(div_index[tile], Engine_Consts.power);


	PTsrcrect.h = PTsrcrect.w = Engine_Consts.Tile_width;

	PTdstrect.x = x - dpyX;
	PTdstrect.y = y - dpyY;
	PTdstrect.h = PTdstrect.w = Engine_Consts.Tile_width;
	SDL_RenderCopy(myrenderer, texture, &(PTsrcrect), &(PTdstrect)); //Same as SDL_BlitSurface but uses the gpu so its faster
}
void  TileLayer::pre_cache(void) {
	unsigned short tileset_cols =(unsigned short) get_config_value<int>(configurators_t::MAP_CONFIG, "tileset_columns");
	for (unsigned short i = 0; i < 255; ++i)
		div_index[i] = i / tileset_cols, mod_index[i] = i % tileset_cols;
}



void TileLayer::Display(SDL_Texture* prev,bool final_layer,SDL_Texture* Tileset,SDL_Renderer* myrenderer) {

	Dim power = Engine_Consts.power;

	if (dpyChanged) {
		auto startCol = DIV_TILE_WIDTH(viewWin.x, power);
		auto startRow = DIV_TILE_HEIGHT(viewWin.y, power);
		auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1, power);
		auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1, power);
		this->dpyX = MOD_TILE_WIDTH(viewWin.x, Engine_Consts.Tile_width);
		this->dpyY = MOD_TILE_WIDTH(viewWin.y, Engine_Consts.Tile_height);

		//viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
		if (prev != nullptr)
			dpybuffer = prev;
		
		
		 //Setting the target of SDL_RenderCopy to be the texture
		SDL_SetRenderTarget(myrenderer, dpybuffer);
		for (unsigned short row = startRow; row <= endRow; ++row)
			for (unsigned short col = startCol; col <= endCol; ++col) {
				if ((map)[row][col] == 0xffff)//clarify this
					continue;
				PutTile(MUL_TILE_WIDTH(col - startCol, Engine_Consts.power), MUL_TILE_HEIGHT(row - startRow, Engine_Consts.power), (map)[row][col], myrenderer, Tileset);
			}
		dpyChanged = false;
		
		 //Unsetting the target of SDL_RenderCopy (now the target is the screen render)
	}
	
	ViewWindow_t PTdstrect{};
	PTdstrect.x = 0;
	PTdstrect.y = 0;
	PTdstrect.h = viewWin.h * scale;
	PTdstrect.w = viewWin.w * scale;//scaled //GWINDOW
	
	if (final_layer) {
		SDL_SetRenderTarget(myrenderer, NULL);
		SDL_RenderCopy(myrenderer, dpybuffer, NULL, &PTdstrect);
	}
}


void TileLayer::scroll_horizon(int dx) {
	viewWin.x += dx;
	if (viewWin.x < 0)
		viewWin.x = 640 + viewWin.x; //40 tiles * 16 pixels = 640
	else
		if (viewWin.x >= 640)
			viewWin.x = viewWin.x - 640;
	dpyChanged = true;
}


bool TileLayer::CanScrollHoriz(int dx) const 
{
	return viewWin.x >= -dx && (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}

bool TileLayer::CanScrollVert( int dy) const 
{
	return viewWin.y >= -dy && (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}

void TileLayer::Scroll(int dx, int dy)
{
	viewWin.x += dx; viewWin.y += dy;
}

void TileLayer::FilterScrollDistance(
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

void TileLayer::FilterScroll(int* dx, int* dy) {
	FilterScrollDistance(viewWin.x, viewWin.w, dx, GetMapPixelWidth());
	FilterScrollDistance(viewWin.y, viewWin.h, dy, GetMapPixelHeight());
}

void TileLayer::ScrollWithBoundsCheck(int dx, int dy) {
	FilterScroll( &dx, &dy);
	Scroll (dx, dy);
	dpyChanged = true;
}