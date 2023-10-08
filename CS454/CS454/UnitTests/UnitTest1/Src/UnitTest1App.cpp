#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/ViewWindow.h"
#include <filesystem>


Render* render_vars;
bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click

void myInput() {
	int CameraPosX, CameraPosY;
	int PrevCameraPosX = 0, PrevCameraPosY = 0;
	
	SDL_Event event;
	const Uint8* keys = SDL_GetKeyboardState((int*)0);
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

				ScrollWithBoundsCheck(&render_vars->ViewWindowR, offsetX, offsetY);
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
				ScrollWithBoundsCheck(&(render_vars->ViewWindowR), 0, 8);
				break;
			case SDLK_UP:
				ScrollWithBoundsCheck(&(render_vars->ViewWindowR), 0, -8);
				break;
			case SDLK_LEFT:
				ScrollWithBoundsCheck(&(render_vars->ViewWindowR), -8, 0);
				break;
			case SDLK_RIGHT:
				ScrollWithBoundsCheck(&(render_vars->ViewWindowR), 8, 0);
				break;
			case SDLK_HOME:
				render_vars->ViewWindowR.x = 0;
				render_vars->ViewWindowR.y = 0;
				break;
			case SDLK_END:
				render_vars->ViewWindowR.x = MUL_TILE_WIDTH(GetMapData()->at(0).size()) - render_vars->ViewWindowR.w;
				render_vars->ViewWindowR.y = MUL_TILE_HEIGHT(GetMapData()->size()) - render_vars->ViewWindowR.h;
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
	SDL_RenderClear(render_vars->myrenderer);
	TileTerrainDisplay(GetMapData(), render_vars->ViewWindowR, { 0, 0,-1,0 }, render_vars->ImgSurface, render_vars->myrenderer,render_vars->Tileset,render_vars->RenderTextureTarget);
	SDL_RenderPresent(render_vars->myrenderer);
	
}

bool myDone() {
	return is_running;
}

void ZeldaApp::Initialise(void) {
	render_vars = new Render(0,0,200,200);
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		render_vars->Gwindow = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (render_vars->Gwindow) std::cout << "Window created!" << std::endl;

		render_vars->myrenderer = SDL_CreateRenderer(render_vars->Gwindow, -1, 0);
		if (render_vars->myrenderer)
		{
			SDL_SetRenderDrawColor(render_vars->myrenderer, 0, 0, 0, 0);
			std::cout << "Renderer created!" << std::endl;
		}
	}

	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests\\UnitTest1\\UnitTest1Media";

	ReadTextMap(full_asset_path + "\\map1_Kachelebene_1.csv");
	render_vars -> ImgSurface = IMG_Load((full_asset_path + "\\overworld_tileset_grass.png").c_str());
	render_vars ->Tileset = SDL_CreateTextureFromSurface(render_vars->myrenderer, render_vars->ImgSurface);
	render_vars->RenderTextureTarget = SDL_CreateTexture(render_vars->myrenderer, 0, SDL_TEXTUREACCESS_TARGET, render_vars->ViewWindowR.w, render_vars->ViewWindowR.h);
	//print();
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