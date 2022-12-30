#include "../Include/ViewWindow.h"

void PutTile(SDL_Rect dstrect, unsigned short x, unsigned short y, SDL_Rect srcrect, Index tile, SDL_Renderer* myrenderer, SDL_Texture* tileTexture) {
	srcrect.x = (tile % 12) * 16;
	srcrect.y = (tile / 12) * 16;
	srcrect.h = srcrect.w = 16;

	dstrect.x = (x) * 48;
	dstrect.y = (y) * 48;
	SDL_RenderCopy(myrenderer, tileTexture, &srcrect, &dstrect);
}

Point viewPosCached { -1, -1 };
void ViewWindow::TileTerrainDisplay(TileMap* map, const Rect& viewWin, const Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer) {
	SDL_Texture* tileTexture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	tileTexture = SDL_CreateTextureFromSurface(myrenderer, ImgSurface);

	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = (viewWin.x / 16);//DIV_TILE_WIDTH(viewWin.x);
		auto startRow = (viewWin.y / 16);//DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = (viewWin.x + viewWin.w - 1)/16;//DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = (viewWin.y + viewWin.y - 1) / 16;//DIV_TILE_HEIGHT(viewWin.y + viewWin.y - 1);
		//dpyX = MOD_TILE_WIDTH(viewWin.x);
		//dpyY = MOD_TILE_WIDTH(viewWin.y);
		//viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
		
		for (unsigned short row = startRow; row <= endRow; ++row)
			for (unsigned short col = startCol; col <= endCol; ++col)
				PutTile(dstrect, row - startRow, col - startCol, srcrect, (*map)[row][col], myrenderer, tileTexture);
				/*PutTile(
					dpyBuffer,
					MUL_TILE_WIDTH(col - startCol),
					MUL_TILE_HEIGHT(row - startRow),
					tiles,
					GetTile(map, col, row)
				);*/

	}

	/*BitmapBlit(
		dpyBuffer,
		{ dpyX, dpyY , viewWin.w, viewWin.h },
		dest,
		{ displayArea.x, displayArea.y }
	);*/
}