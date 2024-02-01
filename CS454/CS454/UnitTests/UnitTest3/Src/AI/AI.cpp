#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/AI/AI.h"
#include "SDL.h"
#include "../../../../Engine/Include/Sprites/SpriteManager.h"
#include "../../Include/SoundManager/SoundManager.h"
CharacterManager &m = CharacterManager::GetSingleton();


bool hasIntersection(Character *c,SDL_Rect v)
{
	SDL_Rect r;
	r = { c->get_start_pos().x, c->get_start_pos().y, 20, 32 };
	return SDL_HasIntersection(&r, &v);
}

void bots(TileLayer* layer){
	auto bots = m.GetTypeList("Palace_bot");
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
	v = { (v.x+100) * layer->get_scale(), v.y * layer->get_scale(), (v.w-180* layer->get_scale()), v.h };

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


void wosu(TileLayer* layer)
{
	auto wosus = m.GetTypeList("Wosu");
	SDL_Rect v = layer->GetViewWindow();
	v = { v.x * layer->get_scale(), v.y * layer->get_scale(), v.w, v.h };

	for (auto& g : wosus) {
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



void mazura(TileLayer *layer)
{
	
	auto mazura = m.GetTypeList("Mazura")[0];
	if(!mazura->is_Alive())
		return;
	SDL_Rect v = layer->GetViewWindow();
	v = { (v.x+150) * layer->get_scale(), v.y * layer->get_scale(), (v.w-170* layer->get_scale()), v.h };
	if (!mazura->is_Active()) {
		if (hasIntersection(mazura, v)){
			auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
			SoundManager::get_singleton().play_music("boss.mp3",2);
			mazura->Start();
			SoundManager::get_singleton().set_vol(50);
		}
	}
	else 
		mazura->progress_character();
	
	
}


void destroy_dead()
{
	for (auto& it : CharacterManager::GetSingleton().Get_dead())
		it->Destroy();
}


void progress_ai(TileLayer *layer){
	guma(layer);
	bots(layer);
	staflos(layer);
	wosu(layer);
	mazura(layer);
	//destroy_dead();//EXPLODE
	
}