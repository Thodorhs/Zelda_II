#include "../Include/ViewWindow.h"

SDL_Rect srcrect;
SDL_Rect dstrect;

void ViewWindow::PutTile(SDL_Surface* WindowSurface, unsigned short x, unsigned short y, Index tile, SDL_Renderer* myrenderer, SDL_Surface* ImgSurface) {
	srcrect.x = (tile % 12) * 16;
	srcrect.y = (tile / 12) * 16;
	srcrect.h = srcrect.w = 16;

	dstrect.x = (x) * 16;
	dstrect.y = (y) * 16;
	dstrect.h = dstrect.w = 16;
	SDL_BlitSurface(ImgSurface, &srcrect, WindowSurface, &dstrect);
	//SDL_BlitScaled(ImgSurface, &srcrect, WindowSurface, &dstrect);
}

Point viewPosCached { -1, -1 };
void ViewWindow::TileTerrainDisplay(TileMap* map, const Rect& viewWin, const Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer, SDL_Window* Gwindow) {

	//std::cout << viewWin
	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = (viewWin.x / 16);//DIV_TILE_WIDTH(viewWin.x);
		auto startRow = (viewWin.y / 16);//DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = (viewWin.x + viewWin.w - 1)/16;//DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = (viewWin.y + viewWin.h - 1)/16;//DIV_TILE_HEIGHT(viewWin.y + viewWin.y - 1);
		//dpyX = MOD_TILE_WIDTH(viewWin.x);
		//dpyY = MOD_TILE_WIDTH(viewWin.y);
		viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
		SDL_Surface* WindowSurface = SDL_GetWindowSurface(Gwindow);
		/*
		std::cout << viewWin.y << "|";
		std::cout << viewWin.h;
		std::cout << std::endl;
		std::cout << "(" << map->size() << ")" << std::endl;
		std::cout << endRow << "|";
		std::cout << endCol; 
		std::cout << std::endl;
		*/

		for (unsigned short row = startRow; row <= endRow; ++row)
			for (unsigned short col = startCol; col <= endCol; ++col) {
				PutTile(WindowSurface, col - startCol, row - startRow, (*map)[row][col], myrenderer, ImgSurface);
			}
		std::cout << "HELLO WORDL" << std::endl;
		SDL_RenderPresent(myrenderer);
		SDL_UpdateWindowSurface(Gwindow);
	}

	SDL_BlitSurface(SDL_GetWindowSurface(Gwindow), NULL, SDL_GetWindowSurface(Gwindow), NULL);
	SDL_UpdateWindowSurface(Gwindow);
}