#include "../../../../Engine/Include/GameLoopFuncs/Input.h"

void InputKeys::InputRead(bool& is_running) {
    SDL_Event event;
    int* dx = new int, * dy = new int;
    *dy = *dy = 0;

	SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			is_running = false;
		}
        if (event.type == SDL_KEYDOWN) {
			SetKeyState(event.key.keysym.sym, true);
        }
        if (event.type == SDL_KEYUP) {
			SetKeyState(event.key.keysym.sym, false);
        }

    }
}


void InputKeys::InputExecution(Link_Class& Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& mouse_down) {
	ViewWin = ActionLayer.GetViewWindow();

	if (isKeyReleased(SDLK_SPACE) == true) {
		distanceJumped = MAXDISTANCEJUMP;
		Link.get_current().GetGravityHandler().gravityAddicted = true;
		Link.get_current().GetGravityHandler().isFalling = true;
	}
		

	if (isKeyPressed(SDLK_d) && isKeyPressed(SDLK_SPACE)) {
		float Scrolldx = 1.0;
		float Scrolldy = 0;
		SDL_Rect LinkRect = Link.get_current().GetBox();

		if (CanJumpCheck(Link, GameGrid) == false) {
			SetAction(Link, "moving_right", "Link.Run.right",
				(FrameRangeAnimator*)Link.get_animator("fr"),
				(FrameRangeAnimation*)Link.get_animation("link.run"),
				30, 8, 0, 1.0);

				if (LinkRect.x - ViewWin.x > ViewWin.w / 2 - 10 && LinkRect.x - ViewWin.x < ViewWin.w / 2 + 10) {
					//std::cout << "im here !" << std::endl;
					ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
					HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
				}
				return;
		}

		SetAction(Link, "link_jump_right", "Link.jump.right" ,
			(MovingAnimator*)Link.get_animator("jump"),
			(MovingAnimation*)Link.get_animation("link.jump"),
			30, 8, -8, 1.0);

		if (LinkRect.x - ViewWin.x > ViewWin.w / 2 - 10 && LinkRect.x - ViewWin.x < ViewWin.w / 2 + 10) {
			//std::cout << "im here !" << std::endl;
			ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
			HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
		}
		distanceJumped += -8;
		return;
	}

	if (isKeyPressed(SDLK_a) && isKeyPressed(SDLK_SPACE)) {
		float Scrolldx = -1.0;
		float Scrolldy = 0;
		SDL_Rect LinkRect = Link.get_current().GetBox();

		if (CanJumpCheck(Link, GameGrid) == false) {
			SetAction(Link, "moving_left", "Link.Run.left",
				(FrameRangeAnimator*)Link.get_animator("fr"),
				(FrameRangeAnimation*)Link.get_animation("link.run"),
				30, -8, 0, -1.0);

			if (LinkRect.x - ViewWin.x > ViewWin.w / 2 - 10 && LinkRect.x - ViewWin.x < ViewWin.w / 2 + 10) {
				ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
				HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
			}
			return;
		}
		SetAction(Link, "link_jump_left", "Link.jump.left", 
			(MovingAnimator*)Link.get_animator("jump"),
			(MovingAnimation*)Link.get_animation("link.jump"), 
			30, -8, -8, -1.0);
		if (LinkRect.x - ViewWin.x > ViewWin.w / 2 - 10 && LinkRect.x - ViewWin.x < ViewWin.w / 2 + 10) {
			ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
			HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
		}
		distanceJumped += -8;
		return;
	}

	if (isKeyPressed(SDLK_SPACE) == true) {
		std::string State; std::string film;
		if (Link.get_current().get_state() == "moving_right") { State = "moving_right"; film = "Link.jump.right"; }
		else { State = "moving_left"; film = "Link.jump.left"; }
		
		if (CanJumpCheck(Link, GameGrid) == false) return;

		SetAction(Link, State, film,
			(MovingAnimator*)Link.get_animator("jump"),
			(MovingAnimation*)Link.get_animation("link.jump"),
			30, 0, -8, 0);
		distanceJumped += -8;
		return;
	}

	if (isKeyPressed(SDLK_a)) {
		float Scrolldx = -1.0;
		float Scrolldy = 0;
		SDL_Rect LinkRect = Link.get_current().GetBox();

		bool CheckMoveWin = SetAction(Link, "moving_left", "Link.Run.left",
			(FrameRangeAnimator*)Link.get_animator("fr"),
			(FrameRangeAnimation*)Link.get_animation("link.run"),
			50, -8.0, 0, -1.0);

		if (LinkRect.x - ViewWin.x > ViewWin.w / 2 - 10 && LinkRect.x - ViewWin.x < ViewWin.w / 2 + 10) {
			ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
			HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
		}
		return;
	}

	if (isKeyPressed(SDLK_d) == true) {
		float Scrolldx = 1.0;
		float Scrolldy = 0;
		SDL_Rect LinkRect = Link.get_current().GetBox();

		bool CheckMoveWin = SetAction(Link, "moving_right", "Link.Run.right",
			(FrameRangeAnimator*)Link.get_animator("fr"),
			(FrameRangeAnimation*)Link.get_animation("link.run"),
			50, 8.0, 0, 1.0);
		
		if (LinkRect.x - ViewWin.x > ViewWin.w / 2 - 10 && LinkRect.x - ViewWin.x < ViewWin.w / 2 + 10) {
			ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
			HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
		}
		return;
	}
	
	if (isKeyPressed(SDLK_b) == true) {
		std::string State; std::string film;
		if (Link.get_current().get_state() == "moving_right") { State = "moving_right"; film = "Link.Attack.right"; }
		else { State = "moving_left"; film = "Link.Attack.left"; }

		SetAction(Link, State, film,
			(FrameRangeAnimator*)Link.get_animator("attack"),
			(FrameRangeAnimation*)Link.get_animation("link.attack"),
			20, 0, 0, 0.0);
		return;
	}
}

bool InputKeys::CanJumpCheck(Link_Class& Link, GridLayer& GameGrid) {
	if (GameGrid.IsOnSolidGround(Link.get_current().GetBox())) {
		distanceJumped = 0;
		Link.get_current().GetGravityHandler().gravityAddicted = false;
		Link.get_current().GetGravityHandler().isFalling = false;
		return true;
	}

	if (distanceJumped <= MAXDISTANCEJUMP) {
		Link.get_current().GetGravityHandler().gravityAddicted = true;
		Link.get_current().GetGravityHandler().isFalling = true;
		return false;
	}
}

 void InputKeys::MoveWindowWithLink(Link_Class& link, float Scrolldx, int& dx) {
	 SDL_Rect LinkRect = link.get_current().GetBox();
	 if(dx == 0) return; //if link doesnt move dont move window

	 if (LinkRect.x > ViewWin.w / 2 - 10 && LinkRect.x < ViewWin.w / 2 + 10) {
		 //ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
		// HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);
		 //if (Scrolldx == 0) dx = 0;
	 }
 }

bool InputKeys::SetAction(Link_Class& link, std::string StateCheck, std::string film, auto animator, auto animation, unsigned delay, int dx, int dy, float Scrolldx) {
	if (link.get_current().get_state() == StateCheck)
		if (animator->HasFinished() == false)
			return false;
	
	//MoveWindowWithLink(link, Scrolldx, dx);

	link.get_current().set_state(StateCheck);
	link.get_current().change_film(link.get_film(film));
	link.stop_animators();

	LinkAction(animation, animator, delay, dx, dy);
	return true;
}


void InputKeys::LinkAction(auto animation, auto animator, unsigned delay, int dx, int dy) {
	animation->SetDx(dx);
	if(dy != 0) animation->SetDy(dy);
	animation->SetDelay(delay);
	animator->Start(animation, GetSystemTime());
}
