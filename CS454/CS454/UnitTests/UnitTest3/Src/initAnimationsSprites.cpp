
#include "../Include/initAnimationsSprites.h"


SpriteManager SpriteManager::singleton;



bool Link_animators_Notfinished()
{
		AnimatorManager& animator_manager = AnimatorManager::GetSingleton();
		return (!animator_manager.Get_by_Id("Link")->HasFinished() ||
			!animator_manager.Get_by_Id("link.jump")->HasFinished() ||
			!animator_manager.Get_by_Id("Link_falling")->HasFinished() ||
			!animator_manager.Get_by_Id("Link.Attack")->HasFinished() );
}

void move_Link()
{
	AnimatorManager& animator_manager = AnimatorManager::GetSingleton();
	SpriteManager& s_manager = SpriteManager::GetSingleton();
	if (auto sprite = s_manager.Get_sprite_by_id("Link")) {
		if (!Link_animators_Notfinished()) {
			animator_manager.Get_by_Id("Link")->Start(GetSystemTime());
		}
	}
}

void render_sprite(SDL_Renderer* renderer, TileLayer* layer)
{
	for (SpriteManager& s_manager = SpriteManager::GetSingleton(); auto it : s_manager.GetDisplayList())
	{
		if (it){
			SDL_Rect dst = { 0,0,layer->GetViewWindow().w,layer->GetViewWindow().h };
			it->Display(dst, MakeTileLayerClipper(layer),renderer, layer->GetViewWindow());
		}
	}
}


void generic_gravity_init(TileLayer* layer)
{
	
	SpriteManager& sprite_manager = SpriteManager::GetSingleton();
	for(auto &it : sprite_manager.GetDisplayList())
	{
		MovingAnimation* falling = new MovingAnimation("falling", 0, 0, 8, 40);
		MovingAnimator* animator = new MovingAnimator(it->GetTypeId() + "_falling", falling);
		animator_init(it, animator, falling,[](){},[](){});
		PrepareSpriteGravityHandler(layer, it);
		it->GetGravityHandler().SetOnStartFalling([animator,it]()
			{
				animator->Start(GetSystemTime());
			});

		it->GetGravityHandler().SetOnStopFalling([animator,it]()
			{
				animator->Stop();
			});
	}

}




void init_animations_sprites(SDL_Renderer* renderer,TileLayer* layer) {
	pr_info("starting initialization of sprites and animations!");
	
	init_sprites(layer);
	generic_gravity_init(layer);
	init_elevators(layer);
	init_link(layer);
	init_guma(layer);
	init_bot(layer);
	init_doors(layer);
	init_staflos(layer);
	init_wosus(layer);
	init_characters();
	init_mazura(layer);

}