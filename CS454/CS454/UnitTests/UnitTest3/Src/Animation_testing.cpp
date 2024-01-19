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
	for (SpriteManager& s_manager = SpriteManager::GetSingleton(); auto it : s_manager.GetDisplayList())
	{
		if (it->GetTypeId() == "Link") {
			it->Move(dx, dy);
			//animator_manager.MarkAsSuspended(animator_manager.Get_by_Id("Link"));
			animator_manager.Get_by_Id("Link")->Start(GetSystemTime());
		}
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

void animators_testing(TileLayer *layer,SDL_Renderer *renderer)
{
	Sprite* Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");

	AnimatorManager& manager = AnimatorManager::GetSingleton();
	
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.run", 0, 3,1 , 0, 0, 150);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link",fr_animation);

	animator->SetOnAction([Link](Animator* animator, const Animation& anim) {FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);});
	animator->SetOnStart([](Animator* animator)
	{
		AnimatorManager::GetSingleton().MarkAsRunning(animator);
	});
	animator->SetOnFinish([Link](Animator* animator)
	{
		AnimatorManager::GetSingleton().MarkAsSuspended(animator);
	});
	
	//animator->Start(fr_animation, GetSystemTime());
	
}


void init_tests(SDL_Renderer* renderer,TileLayer* layer) {
	pr_info("testing!!");
	create_and_register_sprites(layer);
	animators_testing(layer,renderer);

}