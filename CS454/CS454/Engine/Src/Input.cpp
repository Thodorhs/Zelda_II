#pragma once
#include "../Include/GameLoopFuncs/Input.h"
#include "../../UnitTests/UnitTest3/Include/initAnimationsSprites.h"
#include "../Include/Animators/AnimatorManager.h"
#include "../Include/Animators/MovingAnimator.h"





void InputKeys::move_pixels_y(int pixels) {
	if (CanScrollVert((global_render_vars->ViewWindowR), pixels))
		Scroll(&(global_render_vars->ViewWindowR), 0, pixels);
}

void InputKeys::init_key_map() {
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_UP, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_DOWN, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_LEFT, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_RIGHT, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_HOME, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_END, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_g, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_a, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_s, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_d, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_w, false));
	pressed_keys.insert(std::make_pair(SDL_KeyCode::SDLK_b, false));

	prevpressed_keys=pressed_keys;
}

Sprite* get_Link()
{
	return SpriteManager::GetSingleton().Get_sprite_by_id("Link");
}

bool InputKeys::KeyDown(SDL_Keycode code){
	return prevpressed_keys[code] && pressed_keys[code];
}
bool InputKeys::KeyPressed(SDL_Keycode code){
	return !prevpressed_keys[code] && pressed_keys[code];
}
bool InputKeys::KeyReleased(SDL_Keycode code){
	return prevpressed_keys[code] && !pressed_keys[code];
}
void InputKeys::move_pixels_x(int pixels) {
	if(pixels < 0 && Action_Layer->GetViewWindow().x - pixels <= 0 )
		return;
	Action_Layer->ScrollWithBoundsCheck(pixels, 0);
	Backround_Layer->ScrollWithBoundsCheck(pixels, 0);

	if (Action_Layer->GetViewWindow().x == 0 )
		return;
	Horizon_Layer->scroll_horizon(pixels);
}


void InputKeys::layers_set(int x,int y)
{
	Action_Layer->SetViewWindow({ x, y, Action_Layer->GetViewWindow().w, Action_Layer->GetViewWindow().h });
	Backround_Layer->SetViewWindow({ x, y, Action_Layer->GetViewWindow().w, Action_Layer->GetViewWindow().h });
}

SDL_Rect prev_link_box;
void handle_animator_movement(int dx,Animator *scroll, Dim scale, SDL_Rect viewin, Sprite* link)
{
	if (AnimatorManager::GetSingleton().Get_by_Id("Link.Attack")->HasFinished()) {
		SDL_Rect curr_link_box = link->GetBox();
		MovingAnimator* mv = dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id("link.move"));
		if (scroll->HasFinished() && AnimatorManager::GetSingleton().Get_by_Id("link.move")->HasFinished()){
			scroll->Start(GetSystemTime());

			mv->SetDx(dx);
			AnimatorManager::GetSingleton().Get_by_Id("link.move")->Start(GetSystemTime());
			move_Link();
		}
	}
}


Uint64 last_scrol_time;
void InputKeys::move() {
	SDL_Rect viewin = Action_Layer->GetViewWindow();
	Dim scale = Action_Layer->get_scale();
	Sprite* link = get_Link();
	Uint64 curr = GetSystemTime();
	

	auto sc = AnimatorManager::GetSingleton().Get_by_Id("scroll_right");
	auto sc_l = AnimatorManager::GetSingleton().Get_by_Id("scroll_left");

	if (!SpriteManager::GetSingleton().Get_sprite_by_id("Link")->CanMove())
		return;
	if(KeyPressed(SDLK_a) || KeyDown(SDLK_a)){
		handle_animator_movement(-1, sc_l, scale, viewin, link);
		//get_Link()->ChangeFilm("Link.Run.left");
	}
	
	if (KeyPressed(SDLK_d) || KeyDown(SDLK_d)) {

		handle_animator_movement(1, sc, scale, viewin, link);
		//get_Link()->ChangeFilm("Link.Run.right");
	}
	if (KeyPressed(SDLK_w) ) {
		//move_Link(0, -LinkSpeed);
		
		auto att = AnimatorManager::GetSingleton().Get_by_Id("Link.Attack");
		auto falling = AnimatorManager::GetSingleton().Get_by_Id("Link_falling");
		auto j = AnimatorManager::GetSingleton().Get_by_Id("link.jump");
		if(att->HasFinished() && falling->HasFinished() && j->HasFinished() )
			AnimatorManager::GetSingleton().Get_by_Id("link.jump")->Start(GetSystemTime());
	}
	if (KeyPressed(SDLK_s) || KeyDown(SDLK_s)) {
		
	}
	if (KeyPressed(SDLK_b) || KeyDown(SDLK_b)) {
		auto anim = AnimatorManager::GetSingleton().Get_by_Id("Link.Attack");
		auto j = AnimatorManager::GetSingleton().Get_by_Id("link.jump");
		auto fall = AnimatorManager::GetSingleton().Get_by_Id("Link_falling");

		if(anim->HasFinished() && j->HasFinished() && fall->HasFinished())
		{
			anim->Start(GetSystemTime());
		}
	}
	if (KeyPressed(SDLK_LEFT) || KeyDown(SDLK_LEFT)) {
		move_pixels_x(-1);
	}
	if (KeyPressed(SDLK_RIGHT) || KeyDown(SDLK_RIGHT)) {
		move_pixels_x(1);
	}
	if (KeyPressed(SDLK_g)) {
		DpyGrid = !DpyGrid;
	}
	if (KeyPressed(SDLK_HOME)) {
		global_render_vars->ViewWindowR.x = 0;
		global_render_vars->ViewWindowR.y = 0;
	}
	if (KeyPressed(SDLK_END)) {
		global_render_vars->ViewWindowR.x = MUL_TILE_WIDTH(GetMapData()->at(0).size(), Engine_Consts.power) - global_render_vars->ViewWindowR.w;
		global_render_vars->ViewWindowR.y = MUL_TILE_HEIGHT(GetMapData()->size(), Engine_Consts.power) - global_render_vars->ViewWindowR.h;
	}
}
void InputKeys::move_horizon() {
	//Horizon_Layer->set_dpy_changed();
	Horizon_Layer->scroll_horizon(1);
	Action_Layer->ScrollWithBoundsCheck(0, 0);
	Backround_Layer->ScrollWithBoundsCheck(0, 0);
}

void InputKeys::update_press(SDL_Keycode code, bool state) {
	KEY_MAP_t::iterator it = pressed_keys.find(code);
	if (it != pressed_keys.end()) {
		it->second = state;
	}
}

void InputKeys::InputRead() {
	Uint64 curr = GetSystemTime();
	if (curr > last + timer_interval) {
		last = curr;
		move_horizon();
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			update_press(event.key.keysym.sym, true);
			break;
		case SDL_KEYUP:
			update_press(event.key.keysym.sym, false);
			break;
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;
		}
	}
}

//void InputKeys::InputExecution(Link_Class& Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, bool& mouse_down);
//void InputKeys::MoveWindowWithLink(Link_Class& link, float Scrolldx, int& dx);
//bool InputKeys::CanJumpCheck(Link_Class& Link, GridLayer& GameGrid);
//bool InputKeys::SetAction(Link_Class& Link, std::string StateCheck, std::string film, auto animator, auto animation, unsigned delay, int dx, int dy, float Scrolldx);
//void InputKeys::LinkAction(auto animation, auto animator, unsigned delay, int dx, int dy);