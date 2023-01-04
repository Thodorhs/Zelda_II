#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/ViewWindow.h"
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

void myRender() {
	SDL_RenderClear(myrenderer);
	GgameWindow.TileTerrainDisplay(Geditor.GetMapData(), ViewWIndowR, { 0, 0,-1,0 }, ImgSurface, myrenderer);
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