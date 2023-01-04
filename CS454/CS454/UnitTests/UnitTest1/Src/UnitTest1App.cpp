#include "../Bin/UnitTest1App.h"
#include "../Bin/ViewWindow.h"
#include <filesystem>

MapEditor Geditor;
ViewWindow GgameWindow;
SDL_Surface* ImgSurface;
SDL_Renderer* myrenderer;
SDL_Window* Gwindow;
Rect ViewWIndowR = { 0,0,320,240 };

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

bool IsTileIndexAssumedEmpty(Index index) { 
	if (index == 61) return false;
	else return true;
}


void ComputeTileGridBlocks1(/*MapEditor Geditor, */ GridIndex * grid) {
	for (auto row = 0; row < 42; ++row) //HEIGHT
		for (auto col = 0; col < 21; ++col) { //WIDTH
			memset(
				grid,
				IsTileIndexAssumedEmpty(Geditor.GetTile(col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE,
				GRID_ELEMENTS_PER_TILE
			);
			grid += GRID_ELEMENTS_PER_TILE;
		}
}

GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) {
	return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;
}


void DisplayGrid(const Rect& viewWin, GridIndex* grid, Dim tileCols /*SDL_Renderer myRenderer*/) {
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

					if (*gridBlock++ && GRID_SOLID_TILE) {
						auto x = sx + colElem * 4;//MUL_GRID_ELEMENT_WIDTH(colElem);
						auto y = sy + rowElem * 4;//MUL_GRID_ELEMENT_HEIGHT(rowElem);
						auto w = GRID_ELEMENT_WIDTH - 1;
						auto h = GRID_ELEMENT_HEIGHT - 1;
						SDL_Rect gridRect;
						gridRect.x = x;
						gridRect.y = y;
						gridRect.w = w;
						gridRect.h = h;
						SDL_RenderDrawRect(myrenderer, &gridRect);
					}
		}
}

GridIndex mygrid[21*42];

void myRender() {
	SDL_RenderClear(myrenderer);
	GgameWindow.TileTerrainDisplay(Geditor.GetMapData(), ViewWIndowR, { 0, 0,-1,0 }, ImgSurface, myrenderer);
	DisplayGrid(ViewWIndowR, mygrid, 21 /*SDL_Renderer myRenderer*/);
	SDL_RenderPresent(myrenderer);
	
}

bool myDone() {
	return is_running;
}

void UnitTest1App::Initialise(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		Gwindow = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (Gwindow) std::cout << "Window created!" << std::endl;

		myrenderer = SDL_CreateRenderer(Gwindow, -1, 0);
		if (myrenderer)
		{
			SDL_SetRenderDrawColor(myrenderer, 255, 0, 0, 0);
			std::cout << "Renderer created!" << std::endl;
		}
	}

	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests\\UnitTest1\\UnitTest1Media";

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

	ComputeTileGridBlocks1(mygrid);
}

void UnitTest1App::Load() {

}

void UnitTest1App::Run() {
	game.MainLoop();
}

void UnitTest1App::RunIteration() {
	game.MainLoopIteration();
}

void UnitTest1App::Clear() {

}