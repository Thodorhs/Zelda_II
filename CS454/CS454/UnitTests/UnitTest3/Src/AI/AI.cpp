#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/AI/AI.h"
#include "SDL.h"
CharacterManager &m = CharacterManager::GetSingleton();

void bots(TileLayer* layer){
	auto bots = m.GetTypeList("Bot");
	SDL_Rect r;
	SDL_Point p;
	SDL_Rect v = layer->GetViewWindow();
	v = { v.x * layer->get_scale(), v.y * layer->get_scale(), v.w, v.h };

	for(auto &g : bots){
		if(!g->is_Active()){
			r = { g->get_start_pos().x, g->get_start_pos().y, 20, 32 };
			if(SDL_HasIntersection(&r, &v)){
				g->Start();
			}
		} else {
			g->progress_character();
		}
	}
}

void guma(TileLayer* layer){
	auto gumas = m.GetTypeList("Guma");
	SDL_Rect r;
	SDL_Point p;
	SDL_Rect v = layer->GetViewWindow();
	v = { v.x * layer->get_scale(), v.y * layer->get_scale(), v.w, v.h };

	for(auto &g : gumas){
		if(!g->is_Active()){
			r = { g->get_start_pos().x, g->get_start_pos().y, 20, 32 };
			if(SDL_HasIntersection(&r, &v)){
				g->Start();
			}
		} else {
			g->progress_character();
		}
	}
}

void progress_ai(TileLayer *layer){
	guma(layer);
	bots(layer);
}