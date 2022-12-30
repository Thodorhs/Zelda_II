#include "../Include/ZeldaApp.h"
#include "../Include/ViewWindow.h"
#include <filesystem>

MapEditor Geditor;
ViewWindow GgameWindow;
SDL_Surface* ImgSurface;
SDL_Renderer* myrenderer;

void myRender() {
	SDL_RenderClear(myrenderer);
	SDL_Event event;

	//SDL_PollEvent(&event);
	//switch (event.type) {

	/*case SDL_MOUSEBUTTONDOWN:
		case SDL_BUTTON_LEFT:
			std::cout << "PEOS";
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&MouseX, &MouseY);
		std::cout << MouseX << ":" << MouseY << std::endl;
		break;*/
	/*case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				CameraPosY = CameraPosY - 0.1;
				break;
			case SDLK_UP:
				CameraPosY = CameraPosY + 0.1;
				break;
			case SDLK_LEFT:
				CameraPosX = CameraPosX + 0.1;
				break;
			case SDLK_RIGHT:
				CameraPosX = CameraPosX - 0.1;
				break;
			default:
				break;
		}
		break;
	}*/

	GgameWindow.TileTerrainDisplay(Geditor.GetMapData(), { 0,0,16,16 }, { 0,0,-1,0 }, ImgSurface, myrenderer);

	//your stuff to render would typically go here.
	SDL_RenderPresent(myrenderer);
}

void ZeldaApp::Initialise(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		SDL_Window* window = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (window) std::cout << "Window created!" << std::endl;

		SDL_Renderer* myrenderer = SDL_CreateRenderer(window, -1, 0);
		if (myrenderer)
		{
			SDL_SetRenderDrawColor(myrenderer, 255, 255, 255, 255);
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

	Geditor.ReadTextMap(full_asset_path + "\\map1_Kachelebene 1.csv");
	ImgSurface = IMG_Load((full_asset_path + "\\overworld_tileset_grass.png").c_str());
	
	Geditor.print();
	game.SetRender(myRender);
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