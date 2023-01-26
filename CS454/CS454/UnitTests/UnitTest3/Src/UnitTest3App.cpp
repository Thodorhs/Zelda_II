#include "../../../Engine/Include/ZeldaApp.h"

#include "../../../Engine/Include/Sprites/GravityHandler.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "Initialise_characters.h"



static InputKeys& InputHandler = InputKeys::GetSingleton();
InputKeys InputKeys::singleton;//this as well ffff u aa

SDL_Surface* TileSetSurface;
SDL_Renderer* GameRenderer;
SDL_Window* GameWindow;

bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click


TileLayer ActionLayer;
TileLayer HorizonLayer;
GridLayer GameGrid;
AnimationFilmHolder AnimationFilmHolder::holder; // Set this so that the Linker can find it


 // Take the singleton



std::string full_asset_path;

SDL_Rect movingrect = {0,0,10,10};
SDL_Rect viewVariable;


void Input() { 
	InputHandler.InputRead(is_running);
	InputHandler.InputExecution(link_cl, ActionLayer, HorizonLayer, GameGrid, movingrect, mouse_down);
}

//sprite displaY FUAA
void Display_all_Sprites() {
	BitmapSurface dest{}; const SDL_Rect dpyArea;  const Clipper clipper;
	for (auto it : sprite_manager.GetDisplayList()) {
		it->Display(dest, dpyArea, clipper, GameRenderer);
	}
}
void Display_Sprite_byType(std::string type) {
	BitmapSurface dest{}; const SDL_Rect dpyArea;  const Clipper clipper;
	for (auto it : sprite_manager.GetTypeList(type)) {
		it->Display(dest, dpyArea, clipper, GameRenderer);
	}
}

//simantiko : i move exei ena themataki einai sinexia se direct motion meta apo ena simeio oso anafora to gravity fua poonaww
void gravity() {
	for (auto it : sprite_manager.GetDisplayList()) {
		if (it->GetGravityHandler().isFalling) {
			*it = it->Move(0, 1);
		}
	}
}
//still link films (only for testing)
//to kanw gia arxi mia global ton enemy link 


void animation_handler() {
	AnimManager.Progress(GetSystemTime());
}

void myRender() {	
	SDL_RenderClear(GameRenderer);
	HorizonLayer.Display(TileSetSurface, GameRenderer, nullptr, false);
	ActionLayer.Display(TileSetSurface, GameRenderer, HorizonLayer.GetBitmap(), true);

	Display_all_Sprites();
	DisplayGrid(ActionLayer.GetViewWindow(), GameGrid.GetBuffer(), MAPWIDTH, GameRenderer);
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
			SDL_SetRenderDrawColor(GameRenderer, 255, 255, 0, 0);
			std::cout << "Renderer created!" << std::endl;
		}
	}

	game.SetInput(Input);
	game.SetRender(myRender);
	game.SetDone(myDone);
	game.SetAnim(animation_handler);
	game.Set_Physics(gravity);
	is_running = true;

}	

void ZeldaApp::Load() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	full_asset_path = half_path + "UnitTests\\UnitTest3\\UnitTest3Media";

	TileSetSurface = IMG_Load((full_asset_path + "\\Terrain\\Zelda-II-Parapa-Palace-Tileset.png").c_str());

	// LAYERS
	ReadTextMap(full_asset_path + "\\Terrain\\TileMap_Backround.csv");
	HorizonLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()));

	ClearMap(); // We write the data to a static global vector map so we need to clear it before  we read the data of the next layer

	ReadTextMap(full_asset_path + "\\Terrain\\TileMap_Foreground.csv");
	GameGrid = GridLayer(MAPHEIGHT, MAPWIDTH);
	ActionLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()), &GameGrid);

	FilmHolder.Load(full_asset_path, FilmParser, GameRenderer);
	// ANIMATIONS
	initialise_link(GameGrid);
	initialise_enemies(GameGrid);
	//initialise_films_enemy_link();
	//init_enemy_sprite();
	
	
}

void ZeldaApp::Run() {
	
	game.MainLoop();

}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {
		
}