#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/TileLayer.h"
#include "../../../Engine/Include/GridLayer.h"
#include <filesystem>

SDL_Surface* TileSetSurface;
SDL_Renderer* GameRenderer;
SDL_Window* GameWindow;

bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click

GridLayer GameGrid;
TileLayer TileLayerObj;

SDL_Rect movingrect = {0,0,10,10};
SDL_Rect viewVariable;

void myInput() {
	int CameraPosX, CameraPosY;
	int PrevCameraPosX = 0, PrevCameraPosY = 0;
	SDL_Event event;
	int* dx = new int;
	int* dy = new int;
	*dx = 0;
	*dy = 0;
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
				TileLayerObj.Scroll(offsetX, offsetY);
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
				TileLayerObj.Scroll(0, 8);
				break;
			case SDLK_UP:
				TileLayerObj.Scroll(0, -8);
				break;
			case SDLK_LEFT:
				TileLayerObj.Scroll(-8, 0);
				break;
			case SDLK_RIGHT:
				TileLayerObj.Scroll(8, 0);
				break;
			case SDLK_HOME:
				TileLayerObj.SetViewWindow({ 0, 0, TileLayerObj.GetViewWindow().w, TileLayerObj.GetViewWindow().h });
				break;
			case SDLK_END:
				int newX, newY;
				newX = MUL_TILE_WIDTH(GetMapData()->at(0).size()) - TileLayerObj.GetViewWindow().w;
				newY = MUL_TILE_HEIGHT(GetMapData()->size()) - TileLayerObj.GetViewWindow().h;
				TileLayerObj.SetViewWindow({ newX, newY, TileLayerObj.GetViewWindow().w, TileLayerObj.GetViewWindow().h });
				break;
			case SDLK_w:
				*dx = 0;
				*dy = -1;
				break;
			case SDLK_a:
				*dx = -1;
				*dy = 0;
				break;
			case SDLK_s:
				*dx = 0;
				*dy = 1;
				break;
			case SDLK_d:
				*dx = 1;
				*dy = 0;
				break;
			default:
				*dx = 0;
				*dy = 0;
				break;
			}
			break;
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;
		}
		//IF WE WANT TO GET THE TRUE POSITION OF THE RECTANGLE IF THE CAMERA MOVES SO THAT THE GRID WORKS
		GameGrid.FilterGridMotion(movingrect, dx, dy);
		movingrect.x += *dx;
		movingrect.y += *dy;
	}
}



void myRender() {	
	SDL_RenderClear(GameRenderer);
	TileLayerObj.Display(GetMapData(), TileSetSurface, GameRenderer);
	DisplayGrid(TileLayerObj.GetViewWindow(), GameGrid.GetBuffer(), 21, GameRenderer);
	SDL_RenderDrawRect(GameRenderer, &movingrect);
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

	game.SetInput(myInput);
	game.SetRender(myRender);
	game.SetDone(myDone);
	is_running = true;

}	

void ZeldaApp::Load() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests\\UnitTest2\\UnitTest2Media";

	ReadTextMap(full_asset_path + "\\map1_Kachelebene 1.csv");
	TileSetSurface = IMG_Load((full_asset_path + "\\overworld_tileset_grass.png").c_str());

	SDL_Color testcolor{};
	testcolor.r, testcolor.g, testcolor.b, testcolor.a = 232, 123, 132, 100;
	GameGrid = GridLayer(42, 21);
	TileLayerObj = TileLayer(42, 21, *(TileSetSurface), &GameGrid);
}

void ZeldaApp::Run() {
	game.MainLoop();
}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {
		
}