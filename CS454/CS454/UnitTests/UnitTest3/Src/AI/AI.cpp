#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/AI/AI.h"
#include "SDL.h"
CharacterManager &m = CharacterManager::GetSingleton();


bool hasIntersection(Character *c,SDL_Rect v)
{
	SDL_Rect r;
	r = { c->get_start_pos().x, c->get_start_pos().y, 20, 32 };
	return SDL_HasIntersection(&r, &v);
}

void bots(TileLayer* layer){
	auto bots = m.GetTypeList("Bot");
	SDL_Rect v = layer->GetViewWindow();
	v = { v.x * layer->get_scale(), v.y * layer->get_scale(), v.w, v.h };
	for(auto &g : bots){
		if(!g->is_Active()){
			if(hasIntersection(g,v)){
				g->Start();
			}
		} else {
			g->progress_character();
		}
	}
}

void guma(TileLayer* layer){
	auto gumas = m.GetTypeList("Guma");
	SDL_Rect v = layer->GetViewWindow();
	v = { v.x * layer->get_scale(), v.y * layer->get_scale(), v.w, v.h };

	for(auto &g : gumas){
		if(!g->is_Active()){
			if(hasIntersection(g,v)){
				g->Start();
			}
		} else {
			g->progress_character();
		}
	}
}


void staflos(TileLayer* layer)
{
	auto staflos = m.GetTypeList("Staflos");
	SDL_Rect v = layer->GetViewWindow();
	v = { v.x * layer->get_scale(), v.y * layer->get_scale(), v.w, v.h };

	for (auto& g : staflos) {
		if (!g->is_Active()) {
			if (hasIntersection(g, v)) {
				g->Start();
			}
		}
		else {
			g->progress_character();
		}
	}
}

void progress_ai(TileLayer *layer){
	guma(layer);
	bots(layer);
	staflos(layer);
}