#include "../Include/ZeldaApp.h"
#include "../Include/ViewWindow.h"
#include <filesystem>

MapEditor Geditor;
ViewWindow GgameWindow;
SDL_Surface* ImgSurface;
SDL_Renderer* myrenderer;
SDL_Window* Gwindow;
Rect ViewWIndowR = { 0,0,320,240 };
//GridIndex* mygrid;

int CameraPosX, CameraPosY;
int PrevCameraPosX = 0, PrevCameraPosY = 0;
bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click

void myInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			if (mouse_down) { // if i am holding down the left click button and i am moving it then scroll..
				int offsetX = 0, offsetY = 0;
				SDL_GetMouseState(&CameraPosX, &CameraPosY);
				if (CameraPosX - PrevCameraPosX > 0) offsetX = 1;
				else if (CameraPosX - PrevCameraPosX < 0) offsetX = -1;

				if (CameraPosY - PrevCameraPosY > 0) offsetY = 1;
				else if (CameraPosY - PrevCameraPosY < 0) offsetY = -1;

				GgameWindow.ScrollWithBoundsCheck(&ViewWIndowR, offsetX, offsetY);
				PrevCameraPosX, PrevCameraPosY = CameraPosX, CameraPosY;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouse_down = true; // i'am holding it down so set it true
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT){
				mouse_down = false; // i realesed it
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				GgameWindow.ScrollWithBoundsCheck(&ViewWIndowR, 0, 8);
				break;
			case SDLK_UP:
				GgameWindow.ScrollWithBoundsCheck(&ViewWIndowR, 0, -8);
				break;
			case SDLK_LEFT:
				GgameWindow.ScrollWithBoundsCheck(&ViewWIndowR, -8, 0);
				break;
			case SDLK_RIGHT:
				GgameWindow.ScrollWithBoundsCheck(&ViewWIndowR, 8, 0);
				break;
			case SDLK_HOME:
				ViewWIndowR.x = 0;
				ViewWIndowR.y = 0;
				break;
			case SDLK_END:
				ViewWIndowR.x = MUL_TILE_WIDTH(Geditor.GetMapData()->at(0).size()) - ViewWIndowR.w;
				ViewWIndowR.y = MUL_TILE_HEIGHT(Geditor.GetMapData()->size()) - ViewWIndowR.h;
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;
		}
	}
}

bool IsTileIndexAssumedEmpty(Index index) { return false; }
/*
void ComputeTileGridBlocks1(MapEditor Geditor, GridIndex* grid) {
	for (auto row = 0; row < MAX_HEIGHT; ++row)
		for (auto col = 0; col < MAX_WIDTH; ++col) {
			memset(
				grid,
				IsTileIndexAssumedEmpty(Geditor.GetTile(col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE,
				GRID_ELEMENTS_PER_TILE
			);
			grid += GRID_ELEMENTS_PER_TILE;
		}
}*/

/*template <typename Tfunc>
void DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols, const Tfunc& display_f) {
	auto startCol = DIV_TILE_WIDTH(viewWin.x);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile)
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
			auto sx = MUL_TILE_WIDTH(colTile - startCol);
			auto sy = MUL_TILE_HEIGHT(rowTile - startRow);
			auto* gridBlock = GetGridTileBlock(rowTile, colTile, tileCols, grid);
			for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
				for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem)
					if (*gridBlock++ & GRID_SOLID_TILE) {
						auto x = sx + MUL_GRID_ELEMENT_WIDTH(colElem);
						auto y = sy + MUL_GRID_ELEMENT_HEIGHT(rowElem);
						auto w = GRID_ELEMENT_WIDTH - 1;
						auto h = GRID_ELEMENT_HEIGHT - 1;
						display_f(dest, x, y, w, h);
					}
		}
}*/

void myRender() {
	SDL_RenderClear(myrenderer);
	GgameWindow.TileTerrainDisplay(Geditor.GetMapData(), ViewWIndowR, { 0, 0,-1,0 }, ImgSurface, myrenderer);
	//ComputeTileGridBlocks1(Geditor, mygrid);

	SDL_RenderPresent(myrenderer);
}

bool myDone() {
	return is_running;
}

void ZeldaApp::Initialise(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		Gwindow = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (Gwindow) std::cout << "Window created!" << std::endl;

		myrenderer = SDL_CreateRenderer(Gwindow, -1, 0);
		if (myrenderer)
		{
			SDL_SetRenderDrawColor(myrenderer, 0, 0, 0, 0);
			std::cout << "Renderer created!" << std::endl;
		}
	}

	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "Engine\\Assets";

	Geditor = MapEditor();
	GgameWindow = ViewWindow();
	GgameWindow.SetMapPixelWidth(336);
	GgameWindow.SetMapPixelHeight(672);

	Geditor.ReadTextMap(full_asset_path + "\\map1_Kachelebene 1.csv");
	ImgSurface = IMG_Load((full_asset_path + "\\overworld_tileset_grass.png").c_str());
	
	Geditor.print();
	game.SetInput(myInput);
	game.SetRender(myRender);
	game.SetDone(myDone);
	is_running = true;
}

void ZeldaApp::Load() {

}

void ZeldaApp::Run() {
	game.MainLoop();
}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {

}