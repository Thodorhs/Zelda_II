#include "../Include/ViewWindow.h"

SDL_Rect srcrect;
SDL_Rect dstrect;

void ViewWindow::PutTile(SDL_Rect dstrect, unsigned short x, unsigned short y, SDL_Rect srcrect, Index tile, SDL_Renderer* myrenderer, SDL_Texture* tileTexture) {
	srcrect.x = (tile % 12) * 16;
	srcrect.y = (tile / 12) * 16;
	srcrect.h = srcrect.w = 16;

	dstrect.x = (x) * 48;
	dstrect.y = (y) * 48;
	dstrect.h = dstrect.w = 48;
	SDL_RenderCopy(myrenderer, tileTexture, &srcrect, &dstrect);
}

Point viewPosCached { -1, -1 };
void ViewWindow::TileTerrainDisplay(TileMap* map, const Rect& viewWin, const Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer, SDL_Window* Gwindow) {
	SDL_Texture* tileTexture;

	tileTexture = SDL_CreateTextureFromSurface(myrenderer, ImgSurface);

	//std::cout << viewWin
	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = (viewWin.x / 16);//DIV_TILE_WIDTH(viewWin.x);
		auto startRow = (viewWin.y / 16);//DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = (viewWin.x + viewWin.w - 1)/16;//DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = (viewWin.y + viewWin.h - 1)/16;//DIV_TILE_HEIGHT(viewWin.y + viewWin.y - 1);
		//dpyX = MOD_TILE_WIDTH(viewWin.x);
		//dpyY = MOD_TILE_WIDTH(viewWin.y);
		//viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
		
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
			for (unsigned short col = startCol; col <= endCol; ++col) 
				PutTile(dstrect, col - startCol, row - startRow, srcrect, (*map)[row][col], myrenderer, tileTexture);
			
				/*PutTile(
					dpyBuffer,
					MUL_TILE_WIDTH(col - startCol),
					MUL_TILE_HEIGHT(row - startRow),
					tiles,
					GetTile(map, col, row)
				);*/
	}
	/*else {
		tileTexture = SDL_CreateTextureFromSurface(myrenderer, SDL_GetWindowSurface(Gwindow));
		SDL_RenderCopy(myrenderer, tileTexture, NULL, NULL);
	}*/


	/*BitmapBlit(
		dpyBuffer,
		{ dpyX, dpyY , viewWin.w, viewWin.h },
		dest,
		{ displayArea.x, displayArea.y }
	);*/
}