#include "../../../../Engine/Include/GameLoopFuncs/Input.h"

void myInput(Sprite* Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& is_running, bool& mouse_down,Link_Class& link) {
	int CameraPosX, CameraPosY;
	int PrevCameraPosX = 0, PrevCameraPosY = 0;
	SDL_Event event;
	int* dx = new int;
	int* dy = new int;
	*dx = 0;
	*dy = 0;
	Sprite s = link.get_current();
	MovingAnimator* mv = (MovingAnimator*)link.get_animator("move");
	FrameRangeAnimator* fr = (FrameRangeAnimator*)link.get_animator("fr");
	MovingAnimation* m_a = (MovingAnimation*)link.get_animation("link.move");
	FrameRangeAnimation* r_a = (FrameRangeAnimation*)link.get_animation("link.run");
	FrameRangeAnimation* f_attack = (FrameRangeAnimation*)link.get_animation("link.attack");
	FrameRangeAnimator* attack = (FrameRangeAnimator*)link.get_animator("attack");
	assert(f_attack && attack);

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
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouse_down = false; // i realesed it
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				HorizonLayer.Scroll(0, 4);
				//ActionLayer.Scroll(0, 4);
				//Link->Move(0, 4);
				break;
			case SDLK_UP:
				HorizonLayer.Scroll(0, -4);
				//ActionLayer.Scroll(0, -4);
				//Link->Move(0, -4);
				break;
			case SDLK_LEFT:
				HorizonLayer.Scroll(-4, 0);
				//ActionLayer.Scroll(-4, 0);
				//Link->Move(-4, 0);
				break;
			case SDLK_RIGHT:
				HorizonLayer.Scroll(4, 0);
				//ActionLayer.Scroll(4, 0);
				//Link->Move(4, 0);
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
				*dy = -8;
				GameGrid.FilterGridMotion(Link->GetBox(), dx, dy);
				link.stop_animators();
				
				
				break;
			case SDLK_a:
				*dx = -5;
				*dy = 0;
				link.get_current().set_state("moving_left");
				link.get_current().change_film(link.get_film("Link.Run.left"));
				//GameGrid.FilterGridMotion(Link->GetBox(), dx, dy);
				link.stop_animators();
				walk_left(m_a, r_a, fr, mv, *dx, *dy);
				break;
			case SDLK_s:
				*dx = 0;
				*dy = 5;
				
				break;
			case SDLK_d:
				*dx = 5;
				*dy = 0;
				link.get_current().set_state("moving_right");
				//GameGrid.FilterGridMotion(Link->GetBox(), dx, dy);
				link.get_current().change_film(link.get_film("Link.Run.right"));
				link.stop_animators();
				
				walk_left(m_a, r_a, fr, mv, *dx, *dy);
				break;
			case SDLK_b:
				if (link.get_current().get_state() == "moving_right") {
					link.get_current().change_film(link.get_film("Link.Attack.right"));
				}else{ link.get_current().change_film(link.get_film("Link.Attack.left")); }
				link.stop_animators();
				
				f_attack->SetDelay(200);
				attack->Start(f_attack, GetSystemTime());

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
	

		//Link->Move(*dx, *dy);
	}
}

void walk_left(MovingAnimation* animation,FrameRangeAnimation *f_animation, FrameRangeAnimator* f_animator, MovingAnimator* m_animator,int dx,int dy) {
	
	
	animation->SetDx(dx);
	animation->SetDy(dy);
	f_animation->SetDx(dx);
	f_animation->SetDy(dy);
	f_animation->SetDelay(200);
	m_animator->Start(animation, GetSystemTime());
	f_animator->Start(f_animation, GetSystemTime());

}
void walk_right(MovingAnimation* animation, FrameRangeAnimation* f_animation, FrameRangeAnimator* f_animator, MovingAnimator* m_animator,int dx,int dy){}

void attack(FrameRangeAnimation* f_animation, FrameRangeAnimator* f_animator,std::string state) {

}