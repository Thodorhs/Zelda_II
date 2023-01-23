#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "Link_test/Link.h"

static Link_Class& link_cl = Link_Class::GetSingleton(); 
#include "../../../Engine/Include/Sprites/GravityHandler.h"
//#include "Link_test/Link.h"

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


void Input() { myInput(Link, ActionLayer, HorizonLayer, GameGrid, movingrect, is_running, mouse_down,link_cl); }

FrameRangeAnimator* fall_antor;
FrameRangeAnimator* attacking;
void initialize_animators() {
	//Animator* moving = new FrameRangeAnimator();
	
   // attacking = new FrameRangeAnimator();
	//attacking->SetOnAction([](Animator* animator, const Animation& anim) {
	//	FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
	//	});
	/*
	fall_antor = new FrameRangeAnimator();
	//fall_antor ->SetOnAction([](Animator* animator, const Animation& anim) {
		//FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		//});

	PrepareSpriteGravityHandler(&GameGrid, Link); // SET GRAVITY HANDLER THAT CHECKS IF LINK IS ON GROUND
	
	Link->GetGravityHandler().gravityAddicted = true;
	Link->GetGravityHandler().SetOnStartFalling([]() {
	Link->change_film(falling);
	Link->SetMover([](const SDL_Rect& r, int* dx, int* dy) {
		Link->SetPos(r.x +0, r.y +*dy);
			});
		});
	Link->GetGravityHandler().SetOnStopFalling([]() {
		Link->change_film(attack_film);
		});
	Link->GetGravityHandler().Check(Link->GetBox());
	fall_antor->Start(fall_test, GetSystemTime()); */
	//attacking->Start(my_fr_animation, GetSystemTime());


	Animator* move = new MovingAnimator();
	Animator* fr = new FrameRangeAnimator();

	Animation* move_anim = new MovingAnimation("link.move",100,0,0,100);
	Animation* run_anim = new FrameRangeAnimation("link.run", 0, 3, 100, 0, 0, 100);
	
	move->SetOnAction([](Animator* animator, const Animation& anim) {
		Sprite_MoveAction(Link, animator, (const MovingAnimation&)anim);
		});
	move->SetOnStart([](Animator* animator) {
		Link->change_film(attack_film);
		});
	move->SetOnFinish([](Animator* animator ){
		Link->change_film(falling);
		});
    
	fr->SetOnAction([](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	fr->SetOnStart([](Animator* animator) {
		Link->change_film(attack_film);
		});
	fr->SetOnFinish([](Animator* animator) {
		Link->change_film(falling);
		});
	
	link_cl.set_animation("link.move", move_anim);
	link_cl.set_animation("link.run", run_anim);
	link_cl.set_animator("move", move);
	link_cl.set_animator("fr", fr);


}


void animation_handler() {
	AnimManager.Progress(GetSystemTime());
}

void myRender() {	
	SDL_RenderClear(GameRenderer);
	HorizonLayer.Display(TileSetSurface, GameRenderer, nullptr, false);
	ActionLayer.Display(TileSetSurface, GameRenderer, HorizonLayer.GetBitmap(), true);

	BitmapSurface dest{}; const SDL_Rect dpyArea;  const Clipper clipper;
	Link->Display(dest, dpyArea, clipper, GameRenderer);

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


	// ANIMATIONS
	FilmHolder.Load(full_asset_path, FilmParser, GameRenderer); // LOAD ANIMATIONS
	AnimationFilm* TestAnimation_film = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack"));
	falling = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run"));
	my_fr_animation = new FrameRangeAnimation("Link.attack", 0, 3, 0, 10, 10, 500);
	fall_test = new FrameRangeAnimation("Link.run", 0, 3, 0, 10, 10, 500);
	Link = new Sprite(10, 10, TestAnimation_film, "peos");
	attack_film = TestAnimation_film;
	Link->SetMover(MakeSpriteGridLayerMover(&GameGrid,Link));
	//Link->Move(1, 0);
	//Link->GetGravityHandler().gravityAddicted = false;
	initialize_animators();
	
}

void ZeldaApp::Run() {
	
	game.MainLoop();

}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {
		
}