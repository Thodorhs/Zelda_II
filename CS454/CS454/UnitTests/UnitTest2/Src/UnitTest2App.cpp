#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/ViewWindow.h"
#include "../../../Engine/Include/GridCompute.h"
#include <filesystem>

SDL_Surface* TileSetSurface;
SDL_Renderer* GameRenderer;
SDL_Window* GameWindow;
SDL_Rect ViewWIndowR = { 0,0,320,240 };

int CameraPosX, CameraPosY;
int PrevCameraPosX = 0, PrevCameraPosY = 0;
bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click

GridIndex mygrid[21 * 42 * GRID_ELEMENTS_PER_TILE];

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

				ScrollWithBoundsCheck(&ViewWIndowR, offsetX, offsetY);
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
				ScrollWithBoundsCheck(&ViewWIndowR, 0, 8);
				break;
			case SDLK_UP:
				ScrollWithBoundsCheck(&ViewWIndowR, 0, -8);
				break;
			case SDLK_LEFT:
				ScrollWithBoundsCheck(&ViewWIndowR, -8, 0);
				break;
			case SDLK_RIGHT:
				ScrollWithBoundsCheck(&ViewWIndowR, 8, 0);
				break;
			case SDLK_HOME:
				ViewWIndowR.x = 0;
				ViewWIndowR.y = 0;
				break;
			case SDLK_END:
				ViewWIndowR.x = MUL_TILE_WIDTH(GetMapData()->at(0).size()) - ViewWIndowR.w;
				ViewWIndowR.y = MUL_TILE_HEIGHT(GetMapData()->size()) - ViewWIndowR.h;
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


void myRender() {	
	SDL_RenderClear(GameRenderer);
	TileTerrainDisplay(GetMapData(), ViewWIndowR, { 0, 0,-1,0 }, TileSetSurface, GameRenderer);
	DisplayGrid(ViewWIndowR, mygrid, 21, GameRenderer);
	SDL_RenderPresent(GameRenderer);
}

bool myDone() {
	return is_running;
}

void ZeldaApp::Initialise(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		GameWindow = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (GameWindow) std::cout << "Window created!" << std::endl;

		GameRenderer = SDL_CreateRenderer(GameWindow, -1, 0);
		if (GameRenderer)
		{
			SDL_SetRenderDrawColor(GameRenderer, 255, 0, 0, 0);
			std::cout << "Renderer created!" << std::endl;
		}
	}

	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests\\UnitTest2\\UnitTest2Media";

	ReadTextMap(full_asset_path + "\\map1_Kachelebene 1.csv");
	TileSetSurface = IMG_Load((full_asset_path + "\\overworld_tileset_grass.png").c_str());
	
	game.SetInput(myInput);
	game.SetRender(myRender);
	game.SetDone(myDone);
	is_running = true;

	ComputeTileGridBlocks1(GetTile, mygrid);
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