#include "../../../Engine/Include/Sprites/Clipper.h"


template <class T> bool clip_rect(
	T x, T y, T w, T h,
	T wx, T wy, T ww, T wh,
	T* cx, T* cy, T* cw, T* ch
) {
	*cw = T(std::min(wx + ww, x + w)) - (*cx = T(std::max(wx, x)));
	*ch = T(std::min(wy + wh, y + h)) - (*cy = T(std::max(wy, y)));
	return *cw > 0 && *ch > 0;
}
bool clip_rect(const SDL_Rect& r, const SDL_Rect& area, SDL_Rect* result,int view_scale) {
	return clip_rect(
		r.x,
		r.y,
		r.w,
		r.h,
		area.x*view_scale,
		area.y*view_scale,
		area.w*view_scale,
		area.h*view_scale,
		&result->x,
		&result->y,
		&result->w,
		&result->h
	);
}



bool Clipper::Clip(const SDL_Rect& r, const SDL_Rect& dpyArea, SDL_Point* dpyPos, SDL_Rect* clippedBox,const Dim layer_scale) const {
	SDL_Rect visibleArea;
	if (!clip_rect(r, view(), &visibleArea,layer_scale))
	{
		clippedBox->w = clippedBox->h = 0; return false;
	}
	else {
		// clippedBox is in ‘r’ coordinates, sub-rectangle of the input rectangle
		clippedBox->x =  visibleArea.x-r.x;
		clippedBox->y =  visibleArea.y-r.y;
		clippedBox->w = visibleArea.w;
		clippedBox->h = visibleArea.h;
		dpyPos->x = dpyArea.x + (visibleArea.x - (view().x)*layer_scale);
		dpyPos->y = dpyArea.y + (visibleArea.y - (view().y)*layer_scale);
		return true;
	}
}
const Clipper MakeTileLayerClipper(TileLayer* layer) {
	return Clipper().SetView(
		[layer](void)
		{ return layer->GetViewWindow(); }
	);
}
