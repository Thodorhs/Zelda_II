#pragma once
#include "ViewWindow.h"
#include "Util/ConfigFuncs.h"
class TileLayer;
typedef  std::map<const std::string,std::unique_ptr<TileLayer>> Layer_container;

class TileLayer {
	private:
		TileMap map;
		Dim totalRows = 0, totalColumns = 0;
		bool dpyChanged = true;
		Dim dpyX = 0, dpyY = 0;
		Point viewPosCached{ -1, -1 };
		SDL_Texture* dpybuffer;
		std::string id;
		ViewWindow_t viewWin;
		void Allocate(void);
		void pre_cache(void);
		Dim scale;

	public:
		TileLayer(SDL_Rect _ViewWin, SDL_Texture* _dpybuffer, TileMap* _map, std::string _id, Dim _scale);
		TileLayer() = default;
		void SetTile(Dim col, Dim row, Index index);
		SDL_Texture* get_bitmap();
		Index GetTile(Dim col, Dim row) const { return (map)[row][col]; }
		Point Pick(Dim x, Dim y) const {
			return { DIV_TILE_WIDTH(x + viewWin.x,Engine_Consts.power),
			DIV_TILE_HEIGHT(y + viewWin.y,Engine_Consts.power) };
		}
		SDL_Rect& GetViewWindow(void) { return viewWin; }
		void SetViewWindow(const SDL_Rect& r) { viewWin = r; dpyChanged = true; }
		void set_dpy_changed() { dpyChanged = true; }
		static int GetPixelWidth(void) { return Engine_Consts.Map_width; }
		static int GetPixelHeight(void) { return Engine_Consts.Map_height; }
		void Scroll(int dx, int dy);
		void FilterScrollDistance(int viewStartCoord, int viewSize, int* d, int maxMapSize);
		void FilterScroll(int* dx, int* dy);
		void ScrollWithBoundsCheck(int dx, int dy);
		bool CanScrollHoriz(int dx) const;
		bool CanScrollVert(int dy) const;
		void PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture);
		void Display();
		void Display(SDL_Texture* prev, bool final_layer, SDL_Texture* Tileset, SDL_Renderer* myrenderer);
		void scroll_horizon(int dx);
		Dim get_scale() { return scale; }
};