#include "../../../../Engine/Include/GameLoopFuncs/Input.h"

void InputKeys::InputRead(bool& is_running) {
    SDL_Event event;
    int* dx = new int, * dy = new int;
    *dy = *dy = 0;

	SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
			SetKeyState(event.key.keysym.sym, true);
        }
        if (event.type == SDL_KEYUP) {
			SetKeyState(event.key.keysym.sym, false);
        }
    }
}


void InputKeys::InputExecution(Link_Class& Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& mouse_down) {
	int* dx = new int; int* dy = new int;
	*dx = 0; *dy = 0;
	
	if (isKeyPressed(SDLK_d) && isKeyPressed(SDLK_SPACE)) {
		SetAction(Link, "link_jump_right", "Link.jump.right" ,
			(MovingAnimator*)Link.get_animator("jump"),
			(MovingAnimation*)Link.get_animation("link.jump"),
			8, -8);
		return;
	}

	if (isKeyPressed(SDLK_a) && isKeyPressed(SDLK_SPACE)) {
		SetAction(Link, "link_jump_left", "Link.jump.left", 
			(MovingAnimator*)Link.get_animator("jump"),
			(MovingAnimation*)Link.get_animation("link.jump"), 
			-8, -8);
		return;
	}

	if (isKeyPressed(SDLK_a)) {
		SetAction(Link, "moving_left", "Link.Run.left", 
			(FrameRangeAnimator*)Link.get_animator("fr"), 
			(FrameRangeAnimation*)Link.get_animation("link.run"), 
			-8, 0);
		return;
	}

	if (isKeyPressed(SDLK_d) == true) {
		SetAction(Link, "moving_right", "Link.Run.right",
			(FrameRangeAnimator*)Link.get_animator("fr"),
			(FrameRangeAnimation*)Link.get_animation("link.run"),
			8, 0);
		return;
	}

	if (isKeyPressed(SDLK_SPACE) == true) {
		std::string State; std::string film;
		if (Link.get_current().get_state() == "moving_right") { State = "moving_right"; film = "Link.jump.right"; }
		else { State = "moving_left"; film = "Link.jump.left"; }

		SetAction(Link, State, film,
			(MovingAnimator*)Link.get_animator("jump"),
			(MovingAnimation*)Link.get_animation("link.jump"),
			0, -8);
		return;
	}

	
	if (isKeyPressed(SDLK_b) == true) {
		std::string State; std::string film;
		if (Link.get_current().get_state() == "moving_right") { State = "moving_right"; film = "Link.Attack.right"; }
		else { State = "moving_left"; film = "Link.Attack.left"; }

		SetAction(Link, State, film,
			(FrameRangeAnimator*)Link.get_animator("attack"),
			(FrameRangeAnimation*)Link.get_animation("link.attack"),
			0, 0);
		return;
	}
}


void InputKeys::SetAction(Link_Class& link, std::string StateCheck, std::string film, auto animator, auto animation, int dx, int dy) {
	if (link.get_current().get_state() == StateCheck)
		if (animator->HasFinished() == false)
			return;

	link.get_current().set_state(StateCheck);
	link.get_current().change_film(link.get_film(film));
	link.stop_animators();

	LinkAction(animation, animator, dx, dy);
}


void InputKeys::LinkAction(auto animation, auto animator, int dx, int dy) {
	animation->SetDx(dx);
	if(dy != 0) animation->SetDy(dy);
	animation->SetDelay(50);
	animator->Start(animation, GetSystemTime());
}
