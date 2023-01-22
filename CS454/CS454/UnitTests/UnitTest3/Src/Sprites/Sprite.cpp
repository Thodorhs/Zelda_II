#include "../../../../Engine/Include/Sprites/Sprite.h"



void Sprite::Display(BitmapSurface dest, const SDL_Rect& dpyArea, const Clipper& clipper, SDL_Renderer* GameRenderer) const {
	SDL_Rect clippedBox;
	SDL_Point dpyPos;
	/*if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {
		SDL_Rect clippedFrame{
		frameBox.x + clippedBox.x,
		frameBox.y + clippedBox.y,
		clippedBox.w,
		clippedBox.h
		};
		MaskedBlit(
			currFilm->GetBitmap(),
			clippedFrame,
			dest,
			dpyPos
		); //the fuck is dis
	}*/
	SDL_Rect test = { frameBox.x, frameBox.y, frameBox.w, frameBox.h };
	SDL_Rect dpyTest = { x, y, frameBox.w, frameBox.h };
	SDL_RenderCopy(GameRenderer, currFilm->GetBitmap(), &test, &dpyTest);
}

const Sprite::Mover MakeSpriteGridLayerMover(GridLayer* gridLayer, Sprite* sprite) {
	return [gridLayer, sprite](const SDL_Rect& r, int* dx, int* dy) {
		// the r is actually awlays the sprite->GetBox():
		assert(r.x == sprite->GetBox().x && 
			   r.y == sprite->GetBox().y && 
			   r.h == sprite->GetBox().h && 
			   r.w == sprite->GetBox().w);
		gridLayer->FilterGridMotion(r, dx, dy);
		if (*dx || *dy){}
			sprite->SetHasDirectMotion(true).Move(*dx, *dy).SetHasDirectMotion(false); //kati einai auto twra den kserw fua
	};
};

bool Sprite::CollisionCheck(const Sprite* s) const {
	//return this->boundingArea->Intersects(*(s->boundingArea));
	return true; //neeed to fix this.
}


void PrepareSpriteGravityHandler(GridLayer* gridLayer, Sprite* sprite) {
	sprite->GetGravityHandler().SetOnSolidGround(
		[gridLayer](const SDL_Rect& r)
		{ return gridLayer->IsOnSolidGround(r); }
	);
}