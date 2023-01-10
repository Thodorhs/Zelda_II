#pragma once
#include "GridLayer.h"
#include "ViewWindow.h"

class TileLayer {
private:
	TileMap map;
	GridLayer* grid = nullptr;
	Dim totalRows = 0, totalColumns = 0;
	Bitmap tileSet;
	SDL_Rect viewWin;
	SDL_Texture* dpyBuffer;

	bool dpyChanged = true; //this has changed to cache VW
	void Allocate(void) {
		/*dpyBuffer = BitmapCreate(
			GetResWidth() + 2 * TILE_WIDTH,
			GetResHeight() + 2 * TILE_HEIGHT
		);*/
	}

public:
	void SetTile(Dim col, Dim row, Index index) { map[row][col] = index;}
	Index GetTile(Dim col, Dim row) const { return map[row][col];};
	void PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture);

	const SDL_Rect& GetViewWindow(void) const { return viewWin;}
	void SetViewWindow(const SDL_Rect& r) { viewWin = r; dpyChanged = true; }
	
	SDL_Texture* GetBitmap(void) const { return dpyBuffer; }
	int GetPixelWidth(void) const { return viewWin.w; }
	int GetPixelHeight(void) const { return viewWin.h; }
	unsigned GetTileWidth(void) const { return DIV_TILE_WIDTH(viewWin.w); }
	unsigned GetTileHeight(void) const { return DIV_TILE_HEIGHT(viewWin.h); }

	void Display(TileMap* map, /*const SDL_Rect& displayArea,*/ SDL_Surface* ImgSurface, SDL_Renderer* myrenderer);
	const SDL_Point Pick(Dim x, Dim y) const;

	void Scroll(float dx, float dy);
	bool CanScrollHoriz(float dx) const;
	bool CanScrollVert(float dy) const;

	auto ToString(void) const -> const std::string; // unparse
	bool FromString(const std::string&); // parse
	void Save(const std::string& path) const
	{
		fclose(WriteText(fopen(path.c_str(), "wt")));
	}
	bool Load(const std::string& path);
	FILE* WriteText(FILE* fp) const
	{
		fprintf(fp, "%s", ToString().c_str()); return fp;
	}
	bool ReadText(FILE* fp); // TODO: carefull generic parsing
	TileLayer();
	TileLayer(Dim _rows, Dim _cols, Bitmap _tileSet, GridLayer* grid);
	//~TileLayer(); // cleanup here with care!
};