#include "../../../Engine/Include/Sprites/Sprite.h"

#include "../../../Engine/Include/Grid/GridMotion.h"

void Sprite::Blit(SDL_Renderer* renderer,const SDL_Rect& src_rect,const SDL_Rect& dest_rect, SDL_Texture* film_bitmap)
{
	SDL_RenderCopy(renderer,film_bitmap, &src_rect, &dest_rect);
}

void Sprite::Display(const SDL_Rect& dpyArea, const Clipper& clipper,SDL_Renderer* renderer) const {
	SDL_Rect clippedBox;
	SDL_Point dpyPos;
	if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {
		SDL_Rect clippedFrame{
		frameBox.x + clippedBox.x,
		frameBox.y + clippedBox.y,
		clippedBox.w,
		clippedBox.h
		};
		SDL_Rect dpyTest = { dpyPos.x , dpyPos.y, clippedBox.w*layer_scale , clippedBox.h*layer_scale  };
		Blit(renderer, clippedFrame,dpyTest, currFilm->GetBitmap());
	}
}


 const Sprite::Mover Sprite::MakeSpriteGridLayerMover(TileLayer *layer, Sprite* sprite)

 {
	layer_scale = layer->get_scale();
	return [layer, sprite](const SDL_Rect& r, int* dx, int* dy) {
		// the r is actually awlays the sprite->GetBox():
		assert(r.x == sprite->GetScaledBox().x
			 &&r.y == sprite->GetScaledBox().y
			 &&r.h == sprite->GetScaledBox().h
			 &&r.w == sprite->GetScaledBox().w);
		layer->get_grid_layer().LayerFilterGridMotion(r, dx, dy);
		//sprite->SetPos(sprite->GetBox().x + *dx, sprite->GetBox().y + *dy);
		if (*dx || *dy) {
			sprite->SetHasDirectMotion(true).Move(*dx, *dy).SetHasDirectMotion(false);
		}
		};
};

 void PrepareSpriteGravityHandler(TileLayer* gridLayer, Sprite* sprite){
 sprite->GetGravityHandler().SetOnSolidGround(
	 [gridLayer](const SDL_Rect& r)
	 { return gridLayer->get_grid_layer().IsOnSolidGround(r); }
 );
}