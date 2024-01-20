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

void animator_init(Sprite* sprite,FrameRangeAnimator *animator,FrameRangeAnimation* fr_animation)
{
	animator->SetOnAction([sprite](Animator* animator, const Animation& anim) {FrameRange_Action(sprite, animator, (const FrameRangeAnimation&)anim); });
	animator->SetOnStart([](Animator* animator)
		{
			AnimatorManager::GetSingleton().MarkAsRunning(animator);
		});
	animator->SetOnFinish([](Animator* animator)
		{
			AnimatorManager::GetSingleton().MarkAsSuspended(animator);
		});
}


void animators_testing(TileLayer *layer,SDL_Renderer *renderer)
{
	Sprite* Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");

	AnimatorManager& manager = AnimatorManager::GetSingleton();
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.run", 0, 3,1 , 0, 0, 150);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link",fr_animation);

	animator_init(Link, animator, fr_animation);

	FrameRangeAnimation* fr_falling = new FrameRangeAnimation("fall", 0, 1, 0, 0, 10, 80);
	FrameRangeAnimator* falling_animator = new FrameRangeAnimator("link_fall", fr_falling);

	animator_init(Link, falling_animator, fr_falling);

	//animator->Start(fr_animation, GetSystemTime());
	
}

void gravity_test(TileLayer *layer)
{
	SpriteManager& s_manager = SpriteManager::GetSingleton();
	auto s = s_manager.Get_sprite_by_id("Link");
	AnimatorManager& animator_man = AnimatorManager::GetSingleton();
	auto animator = animator_man.Get_by_Id("link_fall");
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
	animators_testing(layer,renderer);
	gravity_test(layer);
}