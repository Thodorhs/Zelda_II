#include "../../../Engine/Include/ZeldaApp.h"
#include "../../../Engine/Include/Grid/Grid.h"
#include "../../../Engine/Include/TileLayer.h"
#include "../../../Engine/Include/Util/Print.h"
#include "../../../Engine/Include/Grid/GridMotion.h"
#include "../../../Engine/Include/Grid/GridCompute.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../Engine/Include/Sprites/SpriteManager.h"

#include "../../../Engine/Include/Sprites/SpriteHelpers.h"
#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../Engine/Include/Util/SystemClock.h"

SpriteManager SpriteManager::singleton;

void move_Link(int dx,int dy)
{
	AnimatorManager& animator_manager = AnimatorManager::GetSingleton();
	SpriteManager& s_manager = SpriteManager::GetSingleton();
	if (auto sprite = s_manager.Get_sprite_by_id("Link")) {
		sprite->Move(dx, dy);
			if (!animator_manager.Get_by_Id("Link")->HasFinished())
				return;
		animator_manager.Get_by_Id("Link")->Start(GetSystemTime());
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



void create_and_register_sprites(TileLayer *layer)
{
	AnimationFilmHolder& holder = AnimationFilmHolder::getInstance();
	SpriteManager& manager = SpriteManager::GetSingleton();
	const Clipper clipper = MakeTileLayerClipper(layer);
	auto s_list = get_sprite_name_list();
	for (auto &it : s_list)
	{
		auto [x, y] = get_sprite_start_pos(it);
		Sprite* sprite =new Sprite(x, y, const_cast<AnimationFilm*>(holder.GetFilm(get_sprite_initial_film(it))),it);
		auto f = sprite->MakeSpriteGridLayerMover(layer, sprite);
		sprite->SetMover(f);
	
		manager.Add(sprite);
	}
	
}


void animator_init(Sprite* sprite,Animator *animator,Animation* fr_animation)
{
	animator->SetOnAction(animator->generic_animator_action(sprite));
	animator->SetOnStart([](Animator* animator)
		{
			AnimatorManager::GetSingleton().MarkAsRunning(animator);
		});
	animator->SetOnFinish([](Animator* animator)
		{
			AnimatorManager::GetSingleton().MarkAsSuspended(animator);
		});
}



void animators_testing(TileLayer *layer)
{
	Sprite* Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");

	AnimatorManager& manager = AnimatorManager::GetSingleton();
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.run", 0, 3,1 , 0, 0, 150);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link",fr_animation);

	animator_init(Link, animator, fr_animation);
}

void generic_gravity_init(TileLayer* layer)
{
	MovingAnimation* falling = new MovingAnimation("falling", 0, 0, 10, 80);
	SpriteManager& sprite_manager = SpriteManager::GetSingleton();
	for(auto &it : sprite_manager.GetDisplayList())
	{
		MovingAnimator* animator = new MovingAnimator(it->GetTypeId() + "_falling", falling);
		animator_init(it, animator, falling);
		PrepareSpriteGravityHandler(layer, it);
		it->GetGravityHandler().SetOnStartFalling([animator]()
			{
				animator->Start(GetSystemTime());
			});

		it->GetGravityHandler().SetOnStopFalling([animator]()
			{
				animator->Stop();
			});
	}

}



void gravity_test(TileLayer *layer)
{
	SpriteManager& s_manager = SpriteManager::GetSingleton();
	auto s = s_manager.Get_sprite_by_id("Link");
	AnimatorManager& animator_man = AnimatorManager::GetSingleton();
	auto animator = animator_man.Get_by_Id(s->GetTypeId()+"_falling");
	PrepareSpriteGravityHandler(layer, s);
	s->GetGravityHandler().SetOnStartFalling([animator]()
		{
			animator->Start(GetSystemTime());
		});

	s->GetGravityHandler().SetOnStopFalling([animator]()
		{
			animator->Stop();
		});
}

void init_tests(SDL_Renderer* renderer,TileLayer* layer) {
	pr_info("testing!!");
	create_and_register_sprites(layer);
	animators_testing(layer);
	generic_gravity_init(layer);
	SpriteManager::GetSingleton().Get_sprite_by_id("Guma")->Move(0,1);
}