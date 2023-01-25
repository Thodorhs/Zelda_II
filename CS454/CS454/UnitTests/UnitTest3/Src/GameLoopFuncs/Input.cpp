#include "../../../../Engine/Include/GameLoopFuncs/Input.h"

int c_frame_right = 0;
int prev_frame_right = 0;
int c_frame_left = 0;
int prev_frame_left = 0;

void InputKeys::InputRead(bool& is_running) {
    SDL_Event event;
    int* dx = new int, * dy = new int;
    *dy = *dy = 0;
	int x_vel = 0;

	SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
			SetKeyState(event.key.keysym.sym, true);
			x_vel = 1;
        }
        else if (event.type == SDL_KEYUP) {
			SetKeyState(event.key.keysym.sym, false);
			x_vel = 0;
        }
    }
}


void InputKeys::InputExecution(Link_Class& link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& mouse_down) {
	bool check_state;
	int* dx = new int; int* dy = new int;
	*dx = 0; *dy = 0;
	prev_frame_right = c_frame_right;
	c_frame_right++;
	prev_frame_left = c_frame_left;
	c_frame_left++;
	Sprite s = link.get_current();

	if (isKeyPressed(SDLK_a) == true) {
		link.get_current().set_state("moving_left");
		link.get_current().change_film(link.get_film("Link.Run.left"));
		link.stop_animators();

		FrameRangeAnimation* run_anim_left = (FrameRangeAnimation*)link.get_animation("link.run");
		if (prev_frame_left > run_anim_left->GetEndFrame()) {
			c_frame_left = 0;
			prev_frame_left = 0;
		}

		run_anim_left->SetStartFrame(prev_frame_left);

		*dx = -8; *dy = 0;
		LinkAction(run_anim_left, (FrameRangeAnimator*)link.get_animator("fr"), *dx, *dy);
	}
	
	if (isKeyPressed(SDLK_d) == true) {
		link.get_current().set_state("moving_right");
		link.get_current().change_film(link.get_film("Link.Run.right"));
		link.stop_animators();

		FrameRangeAnimation* run_anim_right = (FrameRangeAnimation*)link.get_animation("link.run");
		if (prev_frame_right > run_anim_right->GetEndFrame()) {
			c_frame_right = 0;
			prev_frame_right = 0;
		}

		run_anim_right->SetStartFrame(prev_frame_right);

		*dx = 8; *dy = 0;
		LinkAction(run_anim_right, (FrameRangeAnimator*)link.get_animator("fr"), *dx, *dy);
		SetKeyState(SDLK_d, false);
	}

	if (isKeyPressed(SDLK_SPACE) == true) {
		check_state = link.get_current().get_state() == "moving_right";
		if (check_state) link.get_current().change_film(link.get_film("Link.jump.right"));
		else link.get_current().change_film(link.get_film("Link.jump.left"));
		link.stop_animators();

		*dx = 0; *dy = -8;

		LinkAction((MovingAnimation*)link.get_animation("link.move"), (MovingAnimator*)link.get_animator("move"), *dx, *dy);
	}
	
	if (isKeyPressed(SDLK_b) == true) {
		check_state = link.get_current().get_state() == "moving_right";
		if (check_state) link.get_current().change_film(link.get_film("Link.Attack.right"));
		else link.get_current().change_film(link.get_film("Link.Attack.left"));
		link.stop_animators();

		*dx = 0; *dy = 0;
		LinkAction((FrameRangeAnimation*)link.get_animation("link.attack"), (FrameRangeAnimator*)link.get_animator("attack"), *dx, *dy);
	}

	keyState.clear();
}
void InputKeys::LinkAction(auto animation, auto animator, int dx, int dy) {
	animation->SetDx(dx);
	animation->SetDy(dy);
	animation->SetDelay(50);
	animator->Start(animation, GetSystemTime());
	SDL_Delay(60);
}
