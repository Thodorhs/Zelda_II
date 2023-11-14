#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/ViewWindow.h"
#include <filesystem>
//#include "../../../Engine/Include/Util/ConfiguratorManager.h"

#include "../../../Engine/Include/Util/ConfigFuncs.h"
#include "../../../Engine/Include/Grid/Grid.h"


Render* render_vars;
Engine_Consts_t Engine_Consts;

bool is_running; //used by done()
bool mouse_down = false; //bool to check if i hold down the the left click
KEY_MAP_t pressed_keys;
KEY_MAP_t released_keys;
std::unique_ptr<_Grid_> grid_class;


void disable_pr() {
	KEY_MAP_t::iterator pr_it;
	for (pr_it = pressed_keys.begin(); pr_it != pressed_keys.end(); pr_it++) {
		pr_it->second = false;
	}
}

void update_keys() {
	KEY_MAP_t::iterator pr_it;

	for (auto it : released_keys) {
		if (it.second) {
			pr_it = pressed_keys.find(it.first);
			pr_it->second = false;
			auto val = released_keys.find(it.first);
			val->second = false;
		}
	}

}


void update_released(Sint32 code, bool state) {
	KEY_MAP_t::iterator it = released_keys.find(code);
	if (it != released_keys.end())
		it->second = state;
}

void update_press(Sint32 code, bool state) {


	KEY_MAP_t::iterator it = pressed_keys.find(code);

	if (it != pressed_keys.end()) {
		it->second = state;
	}

}

void move_tiles_x(int tiles) {
	int scroll_dist = MUL_TILE_WIDTH(tiles, Engine_Consts.power);
	if (CanScrollHoriz((render_vars->ViewWindowR), scroll_dist))
		Scroll(&(render_vars->ViewWindowR), scroll_dist, 0);
}

void move_tiles_y(int tiles) {
	int scroll_dist = MUL_TILE_WIDTH(tiles, Engine_Consts.power);
	if (CanScrollVert((render_vars->ViewWindowR), scroll_dist))
		Scroll(&(render_vars->ViewWindowR), 0, scroll_dist);
}

void move_pixels_x(int pixels) {
	if (CanScrollHoriz((render_vars->ViewWindowR), pixels))
		Scroll(&(render_vars->ViewWindowR), pixels, 0);
}


void move_pixels_y(int pixels) {
	if (CanScrollVert((render_vars->ViewWindowR), pixels))
		Scroll(&(render_vars->ViewWindowR), 0, pixels);
}

void move() {
	for (auto it : pressed_keys) {
		if (it.second) {
			switch (it.first)
			{

			case SDL_KeyCode::SDLK_UP:
				move_pixels_y(-1);
				break;
			case SDL_KeyCode::SDLK_DOWN:
				move_pixels_y(1);
				break;
			case SDL_KeyCode::SDLK_LEFT:
				move_pixels_x(-1);
				break;
			case SDL_KeyCode::SDLK_RIGHT:
				move_pixels_x(1);
				break;
			case SDLK_HOME:
				render_vars->ViewWindowR.x = 0;
				render_vars->ViewWindowR.y = 0;
				break;
			case SDLK_END:
				render_vars->ViewWindowR.x = MUL_TILE_WIDTH(GetMapData()->at(0).size(), Engine_Consts.power) - render_vars->ViewWindowR.w;
				render_vars->ViewWindowR.y = MUL_TILE_HEIGHT(GetMapData()->size(), Engine_Consts.power) - render_vars->ViewWindowR.h;
				break;
			default:
				break;
			}
		}

	}
}

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
				move_pixels_x(offsetX);
				if (CameraPosY - PrevCameraPosY > 0) offsetY = 1;
				else if (CameraPosY - PrevCameraPosY < 0) offsetY = -1;
				move_pixels_y(offsetY);
				//ScrollWithBoundsCheck(&render_vars->ViewWindowR, offsetX, offsetY);
				
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouse_down = true; // i'am holding it down so set it true
				SDL_GetMouseState(&PrevCameraPosX, &PrevCameraPosY);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				//PrevCameraPosY = 0;
				//PrevCameraPosX = 0;
				mouse_down = false; // i realesed it
			}
			break;

		case SDL_KEYDOWN:
			update_press(event.key.keysym.sym, true);
			break;
		case SDL_QUIT:
			is_running = false;
			break;

		case SDL_KEYUP:
			update_released(event.key.keysym.sym, true);
			break;
		default:
			break;
		}

	}

	move();
	disable_pr();
	//update_keys();

}

void myRender() {
	SDL_RenderClear(render_vars->myrenderer);
	
	TileTerrainDisplay(GetMapData(), render_vars->ViewWindowR, { 0, 0,-1,0 }, render_vars->myrenderer, render_vars->Tileset, render_vars->RenderTextureTarget);
	DisplayGrid(render_vars->ViewWindowR, render_vars->myrenderer, grid_class);
	SDL_RenderPresent(render_vars->myrenderer);

}

bool myDone() {
	return is_running;
}




void init_key_map() {
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_UP, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_DOWN, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_LEFT, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_RIGHT, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_HOME, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_END, false));





	released_keys.insert(std::make_pair(SDL_KeyCode::SDLK_UP, false));
	released_keys.insert(std::make_pair(SDL_KeyCode::SDLK_DOWN, false));
}

#include <cmath>
Dim get_2_power(Dim w, Dim h) {
	assert(w == h && (~(w & (w - 1)))); // assert that dims are powers of two
	return (Dim)log2(w);
}

void init_engine_constants() {
	int px_h, px_w;
	Dim tile_h, tile_w, grid_el_w, grid_el_h;
	configurators_t map = configurators_t::MAP_CONFIG;

	px_h = get_config_value<int>(map, "pixel_height");
	px_w = get_config_value<int>(map, "pixel_width");

	tile_h = get_config_value<int>(map, "tile_height");
	tile_w = get_config_value<int>(map, "tile_width");

	grid_el_h = get_config_value<int>(map, "Grid_el_w");
	grid_el_w = get_config_value<int>(map, "Grid_el_h");

	Dim power_tiles = get_2_power(tile_h, tile_w);
	Dim power_grid = get_2_power(grid_el_h, grid_el_w);


	Engine_Consts.Map_height = px_h;
	Engine_Consts.Map_width = px_w;
	Engine_Consts.Tile_height = tile_h;
	Engine_Consts.Tile_width = tile_w;
	Engine_Consts.power = power_tiles;
	Engine_Consts.grid_power = power_grid;
	Engine_Consts.Grid_el_sz = grid_el_h;
	Engine_Consts.map_rows = get_config_value<int>(map, "map_rows");
	Engine_Consts.map_cols = get_config_value<int>(map, "map_columns");
	
	grid_class = std::make_unique<_Grid_>();
	
	
}
void fill_grid() {
	ComputeTileGridBlocks1(GetMapData(), grid_class);
}


void ZeldaApp::Initialise(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		configurators_t map = configurators_t::MAP_CONFIG;
		configurators_t render = configurators_t::RENDER_CONFIG;
		init_configurators();
		int view_w, view_h;
		int scale = get_config_value<int>(render, "view_scale");
		view_w = get_config_value<int>(render, "view_win_w");
		view_h = get_config_value<int>(render, "view_win_h");
		std::cout << "Subsystems Initialised!..." << std::endl;
		render_vars = new Render(0, 0, view_w, view_h, scale);
		int win_w, win_h;
		win_w = get_config_value<int>(render, "render_w_w");
		win_h = get_config_value<int>(render, "render_w_h");
		init_engine_constants();
		

		render_vars->Gwindow = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, 0);
		if (render_vars->Gwindow) std::cout << "Window created!" << std::endl;

		render_vars->myrenderer = SDL_CreateRenderer(render_vars->Gwindow, -1, 0);
		if (render_vars->myrenderer)
		{
			SDL_SetRenderDrawColor(render_vars->myrenderer, 0, 0, 0, 0);
			std::cout << "Renderer created!" << std::endl;
		}
	}


	init_key_map();
	pre_cache();
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests\\UnitTest1\\UnitTest1Media";


	ReadTextMap(full_asset_path + "\\" + get_config_value<std::string>(configurators_t::MAP_CONFIG, "text_map"));
	render_vars->ImgSurface = IMG_Load((full_asset_path + "\\" + get_config_value<std::string>(configurators_t::MAP_CONFIG, "tileset")).c_str());
	fill_grid();
	std::cout << " w=" << render_vars->ImgSurface->w << " h=" << render_vars->ImgSurface->h << std::endl;
	render_vars->Tileset = SDL_CreateTextureFromSurface(render_vars->myrenderer, render_vars->ImgSurface);
	//SDL_FreeSurface(render_vars->ImgSurface);

	int w;
	int h;
	SDL_QueryTexture(render_vars->Tileset,
		NULL, NULL,
		&w, &h);
	std::cout << " w=" << w << " h=" << h << std::endl;

	render_vars->RenderTextureTarget = SDL_CreateTexture(render_vars->myrenderer, 0, SDL_TEXTUREACCESS_TARGET, render_vars->ViewWindowR.w, render_vars->ViewWindowR.h);
	print();
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