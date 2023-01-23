#include "../../../../Engine/Include/GameLoopFuncs/Input.h"
Link_Class Link_Class::singleton;
void myInput(Sprite* Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& is_running, bool& mouse_down,Link_Class& link) {
	int CameraPosX, CameraPosY;
	int PrevCameraPosX = 0, PrevCameraPosY = 0;
	SDL_Event event;
	int* dx = new int;
	int* dy = new int;
	*dx = 0;
	*dy = 0;
	MovingAnimator* mv = (MovingAnimator*)link.get_animator("move");
	FrameRangeAnimator* fr = (FrameRangeAnimator*)link.get_animator("fr");
	MovingAnimation* m_a = (MovingAnimation*)link.get_animation("link.move");
	FrameRangeAnimation* r_a = (FrameRangeAnimation*)link.get_animation("link.run");
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
				//HorizonLayer.Scroll(0, 4);
				//ActionLayer.Scroll(0, 4);
				Link->Move(0, 4);
				break;
			case SDLK_UP:
				//HorizonLayer.Scroll(0, -4);
				//ActionLayer.Scroll(0, -4);
				Link->Move(0, -4);
				break;
			case SDLK_LEFT:
				//HorizonLayer.Scroll(-4, 0);
				//ActionLayer.Scroll(-4, 0);
				Link->Move(-4, 0);
				break;
			case SDLK_RIGHT:
				//HorizonLayer.Scroll(4, 0);
				//ActionLayer.Scroll(4, 0);
				Link->Move(4, 0);
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
				mv->Stop();
				fr->Stop();
				break;
			case SDLK_s:
				*dx = 0;
				*dy = 5;
				mv->Stop();
				fr->Stop();

				m_a->SetDx(*dx);
				m_a->SetDy(*dy);
				mv->Start(m_a, GetSystemTime());
				fr->Start(r_a, GetSystemTime());
				break;
			case SDLK_d:
				*dx = 5;
				*dy = 0;
				mv->Stop();
				fr->Stop();

				m_a->SetDx(*dx);
				m_a->SetDy(*dy);
				mv->Start(m_a, GetSystemTime());
				fr->Start(r_a, GetSystemTime());
				
				//mv->Progress(GetSystemTime());
				//fr->Progress(GetSystemTime());
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
		//GameGrid.FilterGridMotion(Link->GetBox(), dx, dy);

		

		//Link->Move(*dx, *dy);
	}
}