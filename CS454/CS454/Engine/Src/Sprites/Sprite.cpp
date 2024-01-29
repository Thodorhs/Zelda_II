#include "../../../Engine/Include/Sprites/Sprite.h"

#include <algorithm>

#include "../../../Engine/Include/Grid/GridMotion.h"
#include "../../Include/GameLoopFuncs/Input.h"


void Sprite::Blit(SDL_Renderer* renderer,const SDL_Rect& src_rect,const SDL_Rect& dest_rect, SDL_Texture* film_bitmap)
{
	SDL_RenderCopy(renderer,film_bitmap, &src_rect, &dest_rect);
}

bool is_left_attack(std::string id)
{
	std::ranges::transform(id.begin(), id.end(), id.begin(), ::tolower);

	if((id.find("attack") != std::string::npos) && (id.find("left") != std::string::npos)) {
		return true;
	}
	return false;

}

void Sprite::Display(const SDL_Rect& dpyArea, const Clipper& clipper,SDL_Renderer* renderer, const SDL_Rect& view) const {
	SDL_Rect clippedBox;
	SDL_Point dpyPos;
	if (!isVisible)
		return;

	if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox,layer_scale)) {
		SDL_Rect clippedFrame{
		frameBox.x + clippedBox.x,
		frameBox.y + clippedBox.y,
		clippedBox.w,
		clippedBox.h
		};
		
		int offset = 0;
		if (is_left_attack(currFilm->GetId()))
			offset = clippedBox.w  - prevFilm->GetFrameBox(prevframeNo).w;
		SDL_Rect dpyTest = { dpyPos.x- offset*layer_scale, dpyPos.y, clippedBox.w*layer_scale , clippedBox.h*layer_scale  };

		SDL_Rect s1 = this->GetBox();
		s1.x = (s1.x - view.x* layer_scale)- offset*layer_scale;
        s1.y = s1.y - view.y* layer_scale;
		s1.w *= layer_scale;
		s1.h *= layer_scale;
		if(InputKeys::GetSingleton().CanDpyGrid())
			SDL_RenderDrawRect(renderer, &s1);
		Blit(renderer, clippedFrame,dpyTest, currFilm->GetBitmap());
	}
}


 const Sprite::Mover Sprite::MakeSpriteGridLayerMover(TileLayer *layer, Sprite* sprite)

 {
	layer_scale = layer->get_scale();
	layer_viewWin = layer->GetViewWindow();
	return [layer, sprite](const SDL_Rect& r, int* dx, int* dy) {
		// the r is actually awlays the sprite->GetBox():
		int _dx = *dx;
		assert(r.x == sprite->GetScaledBox().x
			 &&r.y == sprite->GetScaledBox().y
			 &&r.h == sprite->GetScaledBox().h
			 &&r.w == sprite->GetScaledBox().w);
		if(!sprite->GetGridIgnore())
			layer->get_grid_layer().LayerFilterGridMotion(r, dx, dy);
		//sprite->SetPos(sprite->GetBox().x + *dx, sprite->GetBox().y + *dy);
		if (*dx || *dy) {
			sprite->SetHasDirectMotion(true).Move(*dx, *dy).SetHasDirectMotion(false);
			if(*dx)
				sprite->SetWall(false);

		}
		else if(!*dx && _dx)
				sprite->SetWall(true);
		};
};

 void PrepareSpriteGravityHandler(TileLayer* gridLayer, Sprite* sprite){
 sprite->GetGravityHandler().SetOnSolidGround(
	 [gridLayer](const SDL_Rect& r)
	 { return gridLayer->get_grid_layer().IsOnSolidGround(r); }
 );
}

bool Sprite::CollisionCheck(const Sprite* s) const{
	
	SDL_Rect s1 = this->GetBox();
	SDL_Rect s2 = s->GetBox();

	int offset_s1 = 0;
	int offset_s2 = 0;
	if(s->GetPrevFilmConst() && is_left_attack(currFilm->GetId()))
		offset_s1 = (GetBox().w - prevFilm->GetFrameBox(prevframeNo).w) * layer_scale;
	
	if(s->GetPrevFilmConst() && is_left_attack(s->Get_film_id()))
		offset_s2= (s2.w - s->GetPrevFilmConst()->GetFrameBox(s->GetPrevFrameNoConst()).w) * layer_scale;

	s1.x = s1.x - layer_viewWin.x * layer_scale - offset_s1;
	s2.x = s2.x - layer_viewWin.x * layer_scale - offset_s2;
	s1.w *= layer_scale;
	s2.w *= layer_scale;
	
	s1.h *= layer_scale;
	s2.h *= layer_scale;

	if(SDL_HasIntersection(&s1,&s2)){
		return true;
	}
	return false;
}
