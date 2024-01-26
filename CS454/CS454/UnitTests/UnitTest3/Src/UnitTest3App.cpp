//#include "../../../Engine/Include/ViewWindow.h"
//#include "../../../Engine/Include/Util/ConfiguratorManager.h"
//#include "../../../Engine/Include/Util/ConfigFuncs.h"
#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/Grid/Grid.h"
#include "../../../Engine/Include/TileLayer.h"
#include "../../../Engine/Include/Util/Print.h"
#include "../../../Engine/Include/Grid/GridMotion.h"
#include "../../../Engine/Include/Grid/GridCompute.h"
#include <filesystem>
#include "../Include/initAnimationsSprites.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../Engine/Include/KeyFrameAnimation/FilmParser.h"
#include "../../../Engine/Include/Util/SystemClock.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../../Engine/Include/Sprites/CollisionChecker.h"
#include "../Include/StatPrinting/StatPrinting.h"
//#include "../Include/Link/Link.h"
//std::unique_ptr<_Grid_> grid_class;

//Link Link::singleton;
size_t layer_num;
Layer_container Layers;
Render* global_render_vars;
TileLayer* Action_Layer;
TileLayer* Horizon_Layer;
TileLayer* Backround_Layer;
Engine_Consts_t Engine_Consts;
InputKeys InputKeys::singleton;
DestructionManager DestructionManager::singleton;

#include "../../../Engine/Include/Animators/AnimatorManager.h"
void animation_handler() {
	AnimatorManager::GetSingleton().Progress(GetSystemTime());
}

#define _GRID_2
//#define _LAYERS_

void show_grid() {
	#ifdef _GRID_2
		DisplayGrid(Action_Layer->GetViewWindow(), global_render_vars->myrenderer, Action_Layer->get_grid_layer(),Action_Layer->get_scale());
	#else
		DisplayGridOld(render_vars->ViewWindowR, render_vars->myrenderer, grid_class);
	#endif
}

void render_layers() {
	//not working for now (who knows)
	size_t n = 1;
	for(auto it = Layers.begin(); it!= Layers.end(); ++it) {
		bool final_layer = n == layer_num ? true : false;
		it->second->Display(n==1 ? nullptr : it->second->get_bitmap(), final_layer, global_render_vars->Tileset, global_render_vars->myrenderer);
		n++;
	}
}

void input_handler(){
	InputKeys::GetSingleton().InputRead();
}

void execute_input(){
	InputKeys::GetSingleton().move();
}

void update_input(){
	InputKeys::GetSingleton().updatePrev();
}

void collision_checking()
{
	CollisionChecker::GetSingleton().Check();
}



void destructions()
{
	DestructionManager::Get().Commit();
}


void myRender() {
	SDL_RenderClear(global_render_vars->myrenderer);
	#ifndef _LAYERS_
	
	Horizon_Layer->Display(nullptr, false,global_render_vars->Tileset, global_render_vars->myrenderer);
	Backround_Layer->Display(Horizon_Layer->get_bitmap(), false, global_render_vars->Tileset,global_render_vars->myrenderer);
	Action_Layer->Display(Backround_Layer->get_bitmap(), true, global_render_vars->Tileset,global_render_vars->myrenderer);
	SDL_SetRenderDrawColor(global_render_vars->myrenderer, 200, 0, 200, 255);

	render_sprite(global_render_vars->myrenderer, Action_Layer);
	render_stats(global_render_vars->myrenderer, Action_Layer);
	#else
	render_layers();
	#endif

	if(InputKeys::GetSingleton().CanDpyGrid())
		show_grid();
	SDL_RenderPresent(global_render_vars->myrenderer);
}

bool myDone() {	return InputKeys::GetSingleton().get_is_running(); }

#include <cmath>
Dim get_2_power(Dim w, Dim h) {
	assert(w == h && (~(w & (w - 1)))); // assert that dims are powers of two
	return (Dim)log2(w);
}

void init_engine_constants() {
	pr_info("Initializing engine constants..");

	configurators_t map = configurators_t::MAP_CONFIG;

	int px_h = get_config_value<int>(map, "pixel_height");
	int px_w = get_config_value<int>(map, "pixel_width");
	Dim tile_h =(Dim) get_config_value<int>(map, "tile_height");
	Dim tile_w =(Dim) get_config_value<int>(map, "tile_width");
	Dim grid_el_h = (Dim)get_config_value<int>(map, "Grid_el_w");
	Dim grid_el_w = (Dim)get_config_value<int>(map, "Grid_el_h");
	Dim power_tiles = get_2_power(tile_h, tile_w);
	Dim power_grid = get_2_power(grid_el_h, grid_el_w);

	Engine_Consts.Map_height = px_h;
	Engine_Consts.Map_width = px_w;
	Engine_Consts.Tile_height = tile_h;
	Engine_Consts.Tile_width = tile_w;
	Engine_Consts.power = power_tiles;
	Engine_Consts.grid_power = power_grid;
	Engine_Consts.Grid_el_sz = grid_el_h;
	Engine_Consts.map_rows = static_cast<Dim>(get_config_value<int>(map, "map_rows"));
	Engine_Consts.map_cols = static_cast<Dim>(get_config_value<int>(map, "map_columns"));
	
	
}


void init_layers(std::string asset_path) {
	
	pr_info("Initializing grid..");
	//FILL GRID
	std::unique_ptr<_Grid_> grid_class = std::make_unique<_Grid_>();
	#ifdef _GRID_2
	ComputeTileGridBlocks(GetMapData(), grid_class); //grid_old supports action layer 
	#else
	ComputeTileGridBlocks1(GetMapData(), grid_class);
	#endif
	pr_info("Initializing layers..");
	#ifdef _LAYERS_

		layer_num = static_cast<size_t> (get_config_value<int>(configurators_t::MAP_CONFIG, "Layer_num"));
		//auto it = std::any_cast<std::map<std::string, std::any>>(mm.at("Horizon"));
		for(size_t i = 0 ; i<layer_num; i++)
		{
			auto mm = get_config_value<Config_data_t>(configurators_t::LAYER_CONFIG, std::to_string(i));
			for(auto itterator = mm.begin(); itterator!= mm.end(); ++itterator)
			{
				auto obj_map = std::any_cast<Config_data_t>(itterator->second);
				Dim scale =static_cast<Dim> (std::any_cast<int>(obj_map.at("view_scale")));
				SDL_Texture *target = SDL_CreateTexture(global_render_vars->myrenderer, 0, SDL_TEXTUREACCESS_TARGET, global_render_vars->ViewWindowR.w, global_render_vars->ViewWindowR.h);
				if (!target) {
					pr_error(SDL_GetError());
					exit(EXIT_FAILURE);
				}
				ReadTextMap(asset_path + std::any_cast<std::string>(obj_map.at("text_map")));
				Layers.insert(std::make_pair(itterator->first, std::make_unique<TileLayer>(global_render_vars->ViewWindowR, target, GetMapData(), itterator->first, scale)));
			}
		}

	#else
	Dim ac_scale  =(Dim)get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_action");
	Dim back_scale=(Dim) get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_back");
	Dim hor_scale =(Dim)get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_hor");

	//for now keep them with the same viewwindow ,it can be changed 
	SDL_Texture* action_target = SDL_CreateTexture(global_render_vars->myrenderer, 0, SDL_TEXTUREACCESS_TARGET, global_render_vars->ViewWindowR.w, global_render_vars->ViewWindowR.h);
	Action_Layer = new TileLayer(global_render_vars->ViewWindowR,action_target,GetMapData(),"action",ac_scale);
	Action_Layer->set_grid_layer(std::move(grid_class));// to do : for other layers as well if they support grid!

	SDL_Texture* horizon_target = SDL_CreateTexture(global_render_vars->myrenderer, 0, SDL_TEXTUREACCESS_TARGET, global_render_vars->ViewWindowR.w, global_render_vars->ViewWindowR.h);
	ReadTextMap(asset_path + get_config_value<std::string>(configurators_t::MAP_CONFIG, "text_map_hor"));
	Horizon_Layer = new TileLayer(global_render_vars->ViewWindowR,horizon_target,GetMapData(),"horizon",hor_scale);

	SDL_Texture* backround_target = SDL_CreateTexture(global_render_vars->myrenderer, 0, SDL_TEXTUREACCESS_TARGET, global_render_vars->ViewWindowR.w, global_render_vars->ViewWindowR.h);
	ReadTextMap(asset_path + get_config_value<std::string>(configurators_t::MAP_CONFIG, "text_map_back"));
	Backround_Layer = new TileLayer(global_render_vars->ViewWindowR,backround_target, GetMapData(),"backround",back_scale);
	
	#endif
}

auto asset_path() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests\\UnitTest3";
	return full_asset_path;
}




AnimationFilmHolder AnimationFilmHolder::FilmHolder_Instance;
void init_films() {
	AnimationFilmHolder& holder = AnimationFilmHolder::getInstance();
	holder.Load(asset_path(), FilmParser, global_render_vars->myrenderer);
	auto f = holder.GetFilm("Link.Run.left");
	
}

void ZeldaApp::Initialise(void) {
	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
	pr_start_msg();

	pr_info("Initializing configurators..");
	std::string full_asset_path = asset_path();
	init_configurators(full_asset_path);
	configurators_t map = configurators_t::MAP_CONFIG;
	configurators_t render = configurators_t::RENDER_CONFIG;

	const int view_w = get_config_value<int>(render, "view_win_w");
	const int view_h = get_config_value<int>(render, "view_win_h");
	int start_x =get_config_value<int>(render, "start_x");
	int start_y = get_config_value<int>(render, "start_y");
	int scale = get_config_value<int>(render, "view_scale_global");

	pr_info("Subsystems Initialised!...");
	global_render_vars = new Render(start_x, start_y, view_w, view_h, scale);
	int win_w = get_config_value<int>(render, "render_w_w");
	int win_h = get_config_value<int>(render, "render_w_h");
	init_engine_constants();

	global_render_vars->Gwindow = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, 0);
	if (global_render_vars->Gwindow) pr_info("Window created!");
		
	global_render_vars->myrenderer = SDL_CreateRenderer(global_render_vars->Gwindow, -1, 0);
	if (global_render_vars->myrenderer) {
		SDL_SetRenderDrawColor(global_render_vars->myrenderer, 0, 0, 0, 0);
		pr_info("Renderer created!");
	}
	
	pre_cache();
	ReadTextMap(full_asset_path + "\\UnitTest3Media\\" + get_config_value<std::string>(configurators_t::MAP_CONFIG, "text_map"));
	global_render_vars->ImgSurface = IMG_Load((full_asset_path + "\\UnitTest3Media\\" + get_config_value<std::string>(configurators_t::MAP_CONFIG, "tileset")).c_str());
	
	init_layers(full_asset_path + "\\UnitTest3Media\\");

	global_render_vars->Tileset = SDL_CreateTextureFromSurface(global_render_vars->myrenderer, global_render_vars->ImgSurface);

	InputKeys::GetSingleton().init_key_map();
	InputKeys::GetSingleton().setlayersinput(Action_Layer, Horizon_Layer, Backround_Layer);
	InputKeys::GetSingleton().setglobal_render_vars(global_render_vars);
	game.SetInput(input_handler);
	game.SetRender(myRender);
	game.SetDone(myDone);
	game.SetInputExec(execute_input);
	game.SetInputUpdate(update_input);
	game.SetAnim(animation_handler);
	game.SetCollisionChecking(collision_checking);
	game.Set_destr(destructions);
	init_films();
	init_animations_sprites(global_render_vars->myrenderer,Action_Layer);
	InputKeys::GetSingleton().set_is_running(true);
	pr_info("Done!");
}

void ZeldaApp::Load() {}

void ZeldaApp::Run() { game.MainLoop(); }

void ZeldaApp::RunIteration() { game.MainLoopIteration(); }

void ZeldaApp::Clear() {}