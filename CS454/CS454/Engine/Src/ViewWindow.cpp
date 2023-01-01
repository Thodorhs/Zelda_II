#include "../Include/ViewWindow.h"

SDL_Rect srcrect;
SDL_Rect dstrect;

void ViewWindow::PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture) {
	srcrect.x = (tile % 12) * 16;
	srcrect.y = (tile / 12) * 16;
	srcrect.h = srcrect.w = 16;

	dstrect.x = (x) * 16;
	dstrect.y = (y) * 16;
	dstrect.h = dstrect.w = 16;
	SDL_RenderCopy(myrenderer, texture, &srcrect, &dstrect); //Same as SDL_BlitSurface but uses the gpu so its faster
}

SDL_Texture* Rendertexture;
Point viewPosCached { -1, -1 };
void ViewWindow::TileTerrainDisplay(TileMap* map, const Rect& viewWin, const Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer) {
	

	//std::cout << viewWin
	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = (viewWin.x / 16);//DIV_TILE_WIDTH(viewWin.x);
		auto startRow = (viewWin.y / 16);//DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = (viewWin.x + viewWin.w - 1)/16;//DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = (viewWin.y + viewWin.h - 1)/16;//DIV_TILE_HEIGHT(viewWin.y + viewWin.y - 1);
		viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(myrenderer, ImgSurface);
		Rendertexture = SDL_CreateTexture(myrenderer, 0, SDL_TEXTUREACCESS_TARGET, viewWin.w, viewWin.h);
		SDL_SetRenderTarget(myrenderer, Rendertexture);

		for (unsigned short row = startRow; row <= endRow; ++row)
			for (unsigned short col = startCol; col <= endCol; ++col) 
				PutTile(col - startCol, row - startRow, (*map)[row][col], myrenderer, texture);
		
		SDL_SetRenderTarget(myrenderer, NULL);
	}


	SDL_RenderCopy(myrenderer, Rendertexture, NULL, NULL);
}