#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/TileLayer.h"
#include "../../../Engine/Include/GridLayer.h"

#include "../../../Engine/Include/AnimationFilmHolder.h"
#include <filesystem>

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
void Animate(const AnimationFilm& film, const Point& at) { //THIS IS FOR TEST ONLY
	Uint32 frameStart;
	uint64_t t = 0;

	film.DisplayFrame(GameRenderer, { at.x, at.y, 35, 35 }, testi);
	frameStart = SDL_GetTicks();
	testi++;
	if (testi > 3) testi = 0;

	Uint32 frameTime = SDL_GetTicks() - frameStart;
	Uint32 frameDelay = 500;
	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
}


void myRender() {	

	SDL_RenderClear(GameRenderer);
	HorizonLayer.Display(TileSetSurface, GameRenderer, nullptr, false);
	ActionLayer.Display(TileSetSurface, GameRenderer, HorizonLayer.GetBitmap(), true);
	Animate(*(FilmHolder.GetFilm("Link.Run")), { 320, 240 });
	

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
	is_running = true;

}	

int testparser(int startPos,
	const std::string& input,
	std::string& idOutput,
	std::string& pathOutput,
	std::vector<SDL_Rect>& rectsOutput) {

	idOutput = "Link.Run";
	pathOutput = full_asset_path + "\\link-sprites.png";

	SDL_Rect test_anim1 = { 0, 0, 34, 34 };
	rectsOutput.push_back(test_anim1);

	SDL_Rect test_anim2 = { 0, 35, 34, 34 };
	rectsOutput.push_back(test_anim2);

	SDL_Rect test_anim3 = { 0, 70, 34, 34 };
	rectsOutput.push_back(test_anim1);

	SDL_Rect test_anim4 = { 0, 105, 34, 34 };
	rectsOutput.push_back(test_anim4);
	return 0;
}

void ZeldaApp::Load() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	full_asset_path = half_path + "UnitTests\\UnitTest3\\UnitTest3Media";

	TileSetSurface = IMG_Load((full_asset_path + "\\Zelda-II-Parapa-Palace-Tileset.png").c_str());

	ReadTextMap(full_asset_path + "\\zeldatest_Tile BgLayer.csv");
	HorizonLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()));

	ClearMap(); // We write the data to a static global vector map so we need to clear it before  we read the data of the next layer

	ReadTextMap(full_asset_path + "\\zeldatest_Tile ActionLayer.csv");
	GameGrid = GridLayer(MAPHEIGHT, MAPWIDTH);
	ActionLayer = TileLayer(MAPHEIGHT, MAPWIDTH, *(TileSetSurface), *(GetMapData()), &GameGrid);

	FilmHolder.Load("TEST", testparser, GameRenderer);
	
}

void ZeldaApp::Run() {
	game.MainLoop();
}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {
		
}