#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/Grid/Grid.h"
#include "../../../Engine/Include/TileLayer.h"
#include "../../../Engine/Include/Util/Print.h"
#include "../../../Engine/Include/Grid/GridMotion.h"
#include "../../../Engine/Include/Grid/GridCompute.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../Engine/Include/Sprites/SpriteManager.h"

#include "../../../Engine/Include/Sprites/SpriteHelpers.h"

SpriteManager SpriteManager::singleton;

void move_Link(int dx,int dy)
{
	for (SpriteManager& s_manager = SpriteManager::GetSingleton(); auto it : s_manager.GetDisplayList())
	{
		if (it->GetTypeId() == "Link")
			it->Move(dx, dy);
	}
}

void render_sprite(SDL_Renderer* renderer, TileLayer* layer)
{
	for (SpriteManager& s_manager = SpriteManager::GetSingleton(); auto it : s_manager.GetDisplayList())
	{
		if (it)
			it->Display(SDL_Surface{}, { layer->GetViewWindow().x,layer->GetViewWindow().y,layer->GetViewWindow().w,layer->GetViewWindow().h }, MakeTileLayerClipper(layer),renderer);
	}
}


Sprite* sprite_test(SDL_Renderer *render, TileLayer* layer) {
	AnimationFilmHolder& holder = AnimationFilmHolder::getInstance();
	const AnimationFilm* film = holder.GetFilm("Link.Run.left");
	const Clipper clipper = MakeTileLayerClipper(layer);
	Sprite* s = new Sprite(40,40,const_cast<AnimationFilm*>(film), "Link");
	SDL_Surface dst{};
	SpriteManager& manager = SpriteManager::GetSingleton();
	manager.Add(s);
	return s;
	
}


void list_sprites()
{
	auto s_list = get_sprite_name_list();
	for (auto it : s_list)
		pr_error(it);
	pr_error(get_sprite_initial_film(s_list.at(0)));
}

void init_tests(SDL_Renderer* renderer,TileLayer* layer) {
	pr_info("testing!!");
	Sprite* s = sprite_test(renderer,layer);
	auto f = s->MakeSpriteGridLayerMover(layer, s);
	s->SetMover(f);
	list_sprites();
	
}