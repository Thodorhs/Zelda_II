#pragma once
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/CreateSprite.h"


Animator::OnStart wosu_start(Sprite* g) {

	return ([g](Animator* anim)
		{
			//AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_framerange")->Start(GetSystemTime());
			generic_start(anim);
		}
	);
}

Animator::OnFinish wosu_finish(Sprite* g) {
	return ([g](Animator* anim)
		{

			generic_stop(anim);
		}
	);
}

Animator::OnAction wosu_action( Sprite* g) {
	return ( [g](Animator* animator, const Animation& anim)
		{
		}
	);
}

Animator::OnFinish wosu_finish_fr(Sprite* g) {
	return ([g](Animator* anim)
		{

			generic_stop(anim);
		}
	);
}


int drops_wosu = 0;
Animator::OnStart wosu_damage_finish(Sprite* g,TileLayer* layer) {

	return ([g, layer](Animator* anim)
		{
			generic_stop(anim);
			anim->Destroy();
			CollisionChecker::GetSingleton().Cancel(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), g);
			CollisionChecker& col = CollisionChecker::GetSingleton();
            SpriteManager& manager = SpriteManager::GetSingleton();
            Sprite* sprite;
            int r = rand() % 3;
            if (r == 0) {
                sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "blue_pot_default", &drops_wosu, layer);
                col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_blue_pot_action);
            }
            else if (r == 1) {
                sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "red_pot_default", &drops_wosu, layer);
                col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_red_pot_action);
            }
            else {
                sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "points_default", &drops_wosu, layer);
                col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_point_action);
            }
            if (sprite != nullptr) {
                SpriteManager::GetSingleton().AddtoMap("drops", sprite);
				SpriteManager::GetSingleton().AddforDisplay("drops", sprite->GetTypeId());
                sprite->Move(0, 1);
            }
			g->Destroy();
			CharacterManager::GetSingleton().Erase(g->GetTypeId(), "Wosu");
			anim->Destroy();
		}
	);
}

Animator::OnAction death_action( Sprite* g) {
	return ([ g](Animator* animator, const Animation& anim)
		{
			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}



Animator::OnStart wosu_damage_start(Sprite* g, FrameRangeAnimator* fr, MovingAnimator* mv) {

	return ([g, mv, fr](Animator* anim)
		{
			CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(),"Wosu")->setHit(true);
			CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(),"Wosu")->set_health(0);
			mv->Stop();
			fr->Stop();
			mv->Destroy();
			fr->Destroy();
			g->ChangeFilm("death_default");
			g->GetGravityHandler().set_gravity_addicted(false);
			generic_start(anim);
		}
	);
}




void init_wosu_animators(TileLayer* layer) {
	auto wosus = SpriteManager::GetSingleton().GetTypeList("Wosu");
	FrameRangeAnimation* fr_w = new FrameRangeAnimation("wosu", 0, 1, 3, 0, 0, 100);
	FrameRangeAnimation* fr_death = new FrameRangeAnimation("wosu.death", 0, 5, 1, 0, 0, 100);
	MovingAnimation* mv_w = new MovingAnimation("wosu_mv",1,5,0,17);
	
	for (auto& g : wosus) {

		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId() + "_framerange", (FrameRangeAnimation*)fr_w->Clone());
		FrameRangeAnimator* death = new FrameRangeAnimator(g->GetTypeId() + "_damage", (FrameRangeAnimation*)fr_death->Clone());
		MovingAnimator* mv_animator = new MovingAnimator(g->GetTypeId() + "_move", (MovingAnimation*)mv_w->Clone());
		
		mv_animator->SetOnAction(mv_animator->generic_animator_action(g));
		mv_animator->SetOnStart(wosu_start(g));
		mv_animator->SetOnFinish(generic_stop);
		if (g->GetTypeId() == "Wosu" || g->GetTypeId() == "Wosu1") {
			g->ChangeFilm("Wosu_right");
			mv_animator->SetDx(4);
		}
		else {
			g->ChangeFilm("Wosu_left");
			mv_animator->SetDx(-4);
		}
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(wosu_finish_fr(g));
		mv->SetOnAction(mv->generic_animator_action(g));

		death->SetOnAction(death->generic_animator_action(g));
		death->SetOnStart(wosu_damage_start(g, mv, mv_animator));
		death->SetOnFinish(wosu_damage_finish(g,layer));
	}
}

void init_wosus(TileLayer* layer) {
	init_wosu_animators(layer);
}