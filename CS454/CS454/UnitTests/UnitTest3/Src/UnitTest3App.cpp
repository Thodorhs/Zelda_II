#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/TileLayer.h"
#include "../../../Engine/Include/Grid/GridLayer.h"

#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../Engine/Include/KeyFrameAnimation/FilmParser.h"

#include "../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../Engine/Include/Sprites/Sprite.h"
#include "../../../Engine/Include/Util/SystemClock.h"

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
AnimationFilm* my_animation;
Sprite* Link;

std::string full_asset_path;

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
				ActionLayer.Scroll(offsetX, offsetY);
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
				//HorizonLayer.Scroll(0, 1);
				ActionLayer.Scroll(0, 4);
				break;
			case SDLK_UP:
				//HorizonLayer.Scroll(0, -1);
				ActionLayer.Scroll(0, -4);
				break;
			case SDLK_LEFT:
				HorizonLayer.Scroll(-1, 0);
				ActionLayer.Scroll(-4, 0);
				break;
			case SDLK_RIGHT:
				HorizonLayer.Scroll(1, 0);
				ActionLayer.Scroll(4, 0);
				break;
			case SDLK_HOME:
				HorizonLayer.SetViewWindow({ 0, 0, HorizonLayer.GetViewWindow().w, HorizonLayer.GetViewWindow().h });
				ActionLayer.SetViewWindow({ 0, 0, ActionLayer.GetViewWindow().w, ActionLayer.GetViewWindow().h });
				break;
			case SDLK_END:
				int newX, newY;
				newX = MUL_TILE_WIDTH(GetMapData()->at(0).size()) - ActionLayer.GetViewWindow().w;
				newY = MUL_TILE_HEIGHT(GetMapData()->size()) - ActionLayer.GetViewWindow().h;
				HorizonLayer.SetViewWindow({ newX, newY, HorizonLayer.GetViewWindow().w, HorizonLayer.GetViewWindow().h });
				ActionLayer.SetViewWindow({ newX, newY, ActionLayer.GetViewWindow().w, ActionLayer.GetViewWindow().h });
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

int testi = 0;

void do_smth() {
	Link->SetFrame(1);
}

void initialize_animators() {
	Animator* moving = new FrameRangeAnimator();
	FrameRangeAnimator* attacking = new FrameRangeAnimator();
	attacking->SetOnAction([](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	
	attacking->Start(my_fr_animation, GetSystemTime());
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

	game.SetInput(myInput);
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
	ReadTextMap(full_asset_path + "\\zeldatest_Tile BgLayer.csv");
	HorizonLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()));

	ClearMap(); // We write the data to a static global vector map so we need to clear it before  we read the data of the next layer

	ReadTextMap(full_asset_path + "\\zeldatest_Tile ActionLayer.csv");
	GameGrid = GridLayer(MAPHEIGHT, MAPWIDTH);
	ActionLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()), &GameGrid);


	// ANIMATIONS
	FilmHolder.Load(full_asset_path, FilmParser, GameRenderer); // LOAD ANIMATIONS
	AnimationFilm* TestAnimation_film = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack"));
	my_fr_animation = new FrameRangeAnimation("Link.attack", 0, 3, 0, 10, 10, 500);
	Link = new Sprite(320, 240, TestAnimation_film, "peos");
	Link->SetMover([](const SDL_Rect& r, int* dx, int* dy) {
		Link->SetPos(r.x + *dx, r.y + *dy);
		});

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