#include "../../../Engine/Include/ZeldaApp.h"

#include "../../../Engine/Include/Sprites/GravityHandler.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../../Engine/Include/Sprites/CollisionChecker.h"
#include "Initialise_characters.h"


static InputKeys& InputHandler = InputKeys::GetSingleton();
InputKeys InputKeys::singleton;//this as well ffff u aa


//this as well ffff u aa

SDL_Surface* TileSetSurface;
SDL_Renderer* GameRenderer;
SDL_Window* GameWindow;

bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click


TileLayer ActionLayer;
TileLayer HorizonLayer;
GridLayer GameGrid;
AnimationFilmHolder AnimationFilmHolder::holder; // Set this so that the Linker can find it

std::string full_asset_path;

int sign_m = 1;

void progress_wosus(GameCharacter *c) {
	FrameRangeAnimator* fr;
	FrameRangeAnimation* fa;
	fr = (FrameRangeAnimator*)c->get_animator("wosu.fr");
	fa = (FrameRangeAnimation*)c->get_animation("wosu.fr.anim");

	if (c->get_animator("Wosu.death.animator") != NULL) {
		fr = (FrameRangeAnimator*)c->get_animator("Wosu.death.animator");
		fa = (FrameRangeAnimation*)c->get_animation("Wosu.death.animation");
		
		if (fr->HasFinished()) {
			CollisionHandler.Cancel(&link_cl.get_current(), &c->get_current());
			character_manager.remove(c, &link_cl.get_current());
			destruction_man.Register(&c->get_current());
			sprite_manager.Remove(&c->get_current());
		}
	}

	if (fr->HasFinished() == false) {
		return;
	}
	fa->SetDx(1);
	fr->Start(fa, GetSystemTime());
}

void progress_guma(GameCharacter *c) {
	FrameRangeAnimator* fr;
	FrameRangeAnimation* fa;

	if (c->get_animator("Guma.death.animator") != NULL) {
		fr = (FrameRangeAnimator*)c->get_animator("Guma.death.animator");
		fa = (FrameRangeAnimation*)c->get_animation("Guma.death.animation");
		
		if (fr->HasFinished()) {
			CollisionHandler.Cancel(&link_cl.get_current(), &c->get_current());
			character_manager.remove(c, &link_cl.get_current());
			destruction_man.Register(&c->get_current());
			sprite_manager.Remove(&c->get_current());
			
		}
		return; 
	}

	FrameRangeAnimator* attack_move;
	FrameRangeAnimation* attack_move_animation;

	attack_move = (FrameRangeAnimator*)c->get_animator("guma.attack_move_animator");
	attack_move_animation = (FrameRangeAnimation*)c->get_animation("guma.attack_move_animation");
	if (attack_move->HasFinished() == false) {
		sign_m = 1;

		return;

	}

	//proj = &proj->Move(-1, 0);
	//sprite_manager.Remove(proj);
	sign_m = -1;
	attack_move_animation->SetDx(sign_m * 1);
	
	attack_move->Start(attack_move_animation, GetSystemTime());
	c->fire_action();
}
void AI_manager() {
	CharacterManager& c = CharacterManager::GetSingleton();
	GameCharacter* g = NULL;
	int i = 0;
	for (auto it : c.get_current_characters()) {
	
		if (it->get_id() == "Guma") {
			progress_guma(it);
		}
		else if (it->get_id() == "Wosu") {
			progress_wosus(it); }
	}
}
void Destruct() {
	destruction_man.Commit();
}

void Input() { 
	link_cl.SetisLinkPressingDown(false);
	InputHandler.InputRead(is_running);
	InputHandler.InputExecution(link_cl, ActionLayer, HorizonLayer, GameGrid, mouse_down);
}

void CollisionChecking() {
	CollisionHandler.Check();
}

//sprite displaY FUAA
void Display_all_Sprites() {
	BitmapSurface dest{}; const Clipper clipper = MakeTileLayerClipper(&ActionLayer);
	auto sprite_list= sprite_manager.GetDisplayList();
	for (auto it : sprite_list) {
		it->Display(dest, { 0, 0, 0, 0 }, clipper, GameRenderer);
	}
}

void Display_Sprite_byType(std::string type) {
	BitmapSurface dest{}; const Clipper clipper = MakeTileLayerClipper(&ActionLayer);
	for (auto it : sprite_manager.GetTypeList(type)) {
		it->Display(dest, { 0, 0, ActionLayer.GetViewWindow().w, ActionLayer.GetViewWindow().h }, clipper, GameRenderer);
		//it->Display(dest, { 0, 0, 0, 0 }, clipper, GameRenderer);
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
	game.SetCollisionChecking(CollisionChecking);
	game.Set_AI(AI_manager);
	game.Set_destr(Destruct);
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

	initialise_elevator(ActionLayer,HorizonLayer);
	
	initialise_enemies(GameGrid);
	//initialise_films_enemy_link();
	//init_enemy_sprite();	ddd
}

void ZeldaApp::Run() {
	
	game.MainLoop();

}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {
		
}