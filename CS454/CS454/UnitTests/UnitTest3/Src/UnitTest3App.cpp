#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../../Engine/Include/Sprites/GravityHandler.h"
#include "../../../Engine/Include/Sprites/SpriteManager.h"
#include "Link_test/GameCharacters.h"
#include "Link_test/Enemytest.h"
static Link_Class& link_cl = Link_Class::GetSingleton();
Link_Class Link_Class::singleton;//this as well ffff u aa

static InputKeys& InputHandler = InputKeys::GetSingleton();
InputKeys InputKeys::singleton;//this as well ffff u aa

SDL_Surface* TileSetSurface;
SDL_Renderer* GameRenderer;
SDL_Window* GameWindow;

bool is_running; //used by done()
bool mouse_down=false; //bool to check if i hold down the the left click

GridLayer GameGrid;
TileLayer ActionLayer;
TileLayer HorizonLayer;

AnimationFilmHolder AnimationFilmHolder::holder; // Set this so that the Linker can find it


static AnimationFilmHolder& FilmHolder = AnimationFilmHolder::getInstance(); // Take the singleton
static AnimatorManager& AnimManager = AnimatorManager::GetSingleton(); // Take the singleton
static SystemClock& my_system_clock = SystemClock::Get();
static SpriteManager& sprite_manager = SpriteManager::GetSingleton();
FrameRangeAnimation* my_fr_animation;
//testtt
FrameRangeAnimation* fall_test;
AnimationFilm* falling;
AnimationFilm* attack_film;
//end
AnimationFilm* my_animation;
Sprite* Link;

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

GameCharacters* enemy = new Enemy();

void initialise_films_enemy_link() {
	AnimationFilm* attack_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.left"));
	enemy->set_film("Link.Attack.left",attack_left);
}
//ENEMYYY
void init_enemy_sprite() {

	//initialise animators
	Animator* attack = new FrameRangeAnimator();
	Animation* attack_anim = new FrameRangeAnimation("link.attack", 0, 3, 1, 0, 0, 100);
	attack->SetOnAction([](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	attack->SetOnStart([](Animator* animator) {

		//Link->change_film(const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run")));
		});
	attack->SetOnFinish([](Animator* animator) {
		//Link->change_film(falling);
		});

	enemy->set_animation("link.attack", attack_anim);
	enemy->set_animator("attack", attack);
	Sprite *en = new Sprite(300, 200, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.right")), "enemy");
	

	en->SetMover(MakeSpriteGridLayerMover(&GameGrid, en));
	PrepareSpriteGravityHandler(&GameGrid,en);


	en->GetGravityHandler().gravityAddicted = true;
	en->GetGravityHandler().SetOnStartFalling(
		[]() {enemy->stop_animators();
	return; });
	en->GetGravityHandler().SetOnStopFalling(
		[]() {
			//Link->GetGravityHandler().isFalling = false;
			//std::cout << "called";
			//Link->SetHasDirectMotion(false);
		});

	sprite_manager.Add(en);
	enemy->set_current(en);
	en->Move(1, 0);
}
//END ENEMY


//LINK
void initialise_films_link() {
	AnimationFilm* run_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.left"));
	AnimationFilm* attack_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.left"));
	AnimationFilm* attack_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.right"));
	AnimationFilm* fall_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.falling.left"));
	AnimationFilm* fall_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.falling.right"));
	AnimationFilm* jump_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.jump.left"));
	AnimationFilm* jump_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.jump.right"));
	link_cl.set_film("Link.Run.left", run_left);
	link_cl.set_film("Link.Attack.left", attack_left);
	link_cl.set_film("Link.Attack.right", attack_right);
	link_cl.set_film("Link.falling.left", fall_left);
	link_cl.set_film("Link.falling.right", fall_right);
	link_cl.set_film("Link.jump.left", jump_left);
	link_cl.set_film("Link.jump.right", jump_right);
}







void Initialise_sprites() {
	Link = new Sprite(200, 200, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.right")), "Link");
	link_cl.set_film("Link.Run.right", const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.right")));
	
	Link->SetMover(MakeSpriteGridLayerMover(&GameGrid, Link));
	PrepareSpriteGravityHandler(&GameGrid, Link);
	

	Link->GetGravityHandler().gravityAddicted = true;
	Link->GetGravityHandler().SetOnStartFalling(
		[]() {link_cl.stop_animators();
					return;});
	Link->GetGravityHandler().SetOnStopFalling(
		[]() {
			//Link->GetGravityHandler().isFalling = false;
			//std::cout << "called";
			//Link->SetHasDirectMotion(false);
		});

	sprite_manager.Add(Link);
}



FrameRangeAnimator* fall_antor;
FrameRangeAnimator* attacking;
void initialize_animators() {
	Animator* move = new MovingAnimator();
	Animation* move_anim = new MovingAnimation("link.move", 1, 0, 0, 100);

	Animator* fr = new FrameRangeAnimator();
	Animation* run_anim = new FrameRangeAnimation("link.run", 0, 3, 1, 0, 0, 0);
	
	Animator* attack = new FrameRangeAnimator();
	Animation* attack_anim = new FrameRangeAnimation("link.attack", 0, 3, 1, 0, 0, 100);

	Animator* jump = new MovingAnimator();
	Animation* jump_anim = new MovingAnimation("link.jump", 1, 0, 0, 40);

	//ATTACK

	attack->SetOnAction([](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	attack->SetOnStart([](Animator* animator) {});
	attack->SetOnFinish([](Animator* animator) {});


	//MOVE

	move->SetOnAction([](Animator* animator, const Animation& anim) {
		Sprite_MoveAction(Link, animator, (const MovingAnimation&)anim);
	});
	move->SetOnStart([](Animator* animator) {});
	move->SetOnFinish([](Animator* animator ){});

    
	fr->SetOnAction([](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	fr->SetOnStart([](Animator* animator) {});
	fr->SetOnFinish([](Animator* animator) {});
	

	jump->SetOnAction([](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
	});
	jump->SetOnStart([](Animator* animator) {});
	jump->SetOnFinish([](Animator* animator) {});

	link_cl.set_animation("link.move", move_anim);
	link_cl.set_animation("link.run", run_anim);

	link_cl.set_animator("move", move);
	link_cl.set_animator("fr", fr);

	link_cl.set_animation("link.attack", attack_anim);
	link_cl.set_animator("attack", attack);

	link_cl.set_animation("link.jump", jump_anim);
	link_cl.set_animator("jump", jump);

	link_cl.set_current(Link);

}
//END LINK

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

	TileSetSurface = IMG_Load((full_asset_path + "\\Zelda-II-Parapa-Palace-Tileset.png").c_str());

	// LAYERS
	ReadTextMap(full_asset_path + "\\Entrance._BackroundEntrance.csv");
	HorizonLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()));

	ClearMap(); // We write the data to a static global vector map so we need to clear it before  we read the data of the next layer

	ReadTextMap(full_asset_path + "\\Entrance._ForegroundEntrance.csv");
	GameGrid = GridLayer(MAPHEIGHT, MAPWIDTH);
	ActionLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()), &GameGrid);

	FilmHolder.Load(full_asset_path, FilmParser, GameRenderer);
	// ANIMATIONS
	Initialise_sprites();
	initialize_animators();
	initialise_films_link();
	initialise_films_enemy_link();
	init_enemy_sprite();
	
	
}

void ZeldaApp::Run() {
	
	game.MainLoop();

}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {
		
}