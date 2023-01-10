#pragma once
#include "GridLayer.h"

class TileLayer {
private:
	Index* map = nullptr;
	GridLayer* grid = nullptr;
	Dim totalRows = 0, totalColumns = 0;
	Bitmap tileSet;
	SDL_Rect viewWin;
	Bitmap dpyBuffer;
	bool dpyChanged = true; //this has changed to cache VW
	Dim dpyX = 0, dpyY = 0;
	void Allocate(void) {
		map = new Index[totalRows * totalColumns];
		dpyBuffer = BitmapCreate(
			GetResWidth() + 2 * TILE_WIDTH,
			GetResHeight() + 2 * TILE_HEIGHT
		);
	}

public:
	void SetTile(Dim col, Dim row, Index index);
	Index GetTile(Dim col, Dim row) const
	{
		return map[row * totalColumns + col];
	}
	const Point Pick(Dim x, Dim y) const {
		return { DIV_TILE_WIDTH(x + viewWin.x),
		DIV_TILE_HEIGHT(y + viewWin.y) };
	}
	const Rect& GetViewWindow(void) const { return viewWin; }
	void SetViewWindow(const Rect& r)
	{
		viewWin = r; dpyChanged = true;
	}
	void Display(Bitmap dest, const Rect& displayArea);
	Bitmap GetBitmap(void) const { return dpyBuffer; }
	int GetPixelWidth(void) const { return viewWin.w; }
	int GetPixelHeight(void) const { return viewWin.h; }
	unsigned GetTileWidth(void) const { return DIV_TILE_WIDTH(viewWin.w); }
	unsigned GetTileHeight(void) const { return DIV_TILE_HEIGHT(viewWin.h); }
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
	TileLayer(Dim _rows, Dim _cols, Bitmap _tileSet);
	~TileLayer(); // cleanup here with care!
};