#pragma once
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/Link/Link.h"
#include "../../Include/CreateSprite.h"
Animator::OnStart staflos_attack_start(Sprite* s) {

	return ([s](Animator* anim)
		{
			AnimatorManager::GetSingleton().Get_by_Id(s->GetTypeId() + "_move")->Stop();
			generic_start(anim);
			if(s->GetFilm()->GetId() == "Staflos.walk.right")
				s->ChangeFilm("Staflos.attack.right");
			else
				s->ChangeFilm("Staflos.attack.left");
		}
	);
}

Animator::OnFinish staflos_attack_finish( Sprite* s) {
	return ([s](Animator* anim)
		{
			generic_stop(anim);

		}
	);
}

Animator::OnAction staflos_attack_action(Sprite* s, TileLayer* layer) {
	return ([layer, s](Animator* animator, const Animation& anim)
		{
			animator->generic_animator_action(s)(animator, anim);
		}
	);
}





Animator::OnStart staflos_start(Sprite *s) {

	return ([s](Animator* anim)
		{
			
			generic_start(anim);
			//s->SetVisibility(true);
			//s->ChangeFilm("Staflos.walk.right");
		}
	);
}

Animator::OnFinish staflos_finish(Sprite* g) {
	return ([g](Animator* anim)
		{

			generic_stop(anim);
			//auto att = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_attack");
			//if (att->HasFinished())
			//	att->Start(GetSystemTime());
		}
	);
}

Animator::OnAction staflos_action( Sprite* g, TileLayer* layer) {
	return ([layer, g](Animator* animator, const Animation& anim)
		{
		auto gr = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_falling");
		if(!gr->HasFinished())
				return;
			
			animator->generic_animator_action(g)(animator, anim);
		}
	);
}



Animator::OnStart staflos_damage_start(Sprite* g, FrameRangeAnimator* mv) {

	return ([g, mv](Animator* anim)
		{
			mv->Stop();
			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Staflos");
			c->setHit(true);
			auto film = g->GetFilm()->GetId();
			auto health = c->get_health() - Link::GetSingleton().get_dps();
			c->set_health(health);
			if (health <= 0) {
				AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_death")->Start(GetSystemTime());
			}
			else {
				if (film == "Staflos.walk.left" || film == "Staflos.attack.left")
					((MovingAnimator*)anim)->SetDx(10);
				else
					((MovingAnimator*)anim)->SetDx(-10);

				generic_start(anim);
			}
		}
	);
}

Animator::OnFinish staflos_damage_finish(Sprite* g) {
	return ([g](Animator* anim)
		{

			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Staflos");

			generic_stop(anim);
			if (!c->is_Alive())
				return;
			if (c->is_Hit()) {
				c->setHit(false);
				//AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move")->Start(GetSystemTime());
			}
		}
	);
}


Animator::OnAction staflos_death_action( Sprite* g) {


	return ([g](Animator* animator, const Animation& anim)
		{
			
			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);

		}
	);
}




Animator::OnStart staflos_death_start(Sprite* g) {

	return ([g](Animator* anim)
		{
			CollisionChecker::GetSingleton().Cancel(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), g);
			Link::GetSingleton().addPoints(30);
			auto mv = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move");
			auto dmg = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_damage");
			g->ChangeFilm("death_default");
			g->GetGravityHandler().set_gravity_addicted(false);
			
			mv->Stop();
			dmg->Stop();
			//mv->Destroy();
			//dmg->Destroy();
			generic_start(anim);
		}
	);
}
int drops_staflos = 0;
Animator::OnFinish staflos_death_finish(Sprite* g,TileLayer *layer) {
	
	return ([g,layer](Animator* anim)
		{

			//CharacterManager::GetSingleton().Erase(g->GetTypeId(), "Guma");
			
			generic_stop(anim);
			anim->Destroy();
			auto mv = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move");
			auto dmg = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_damage");
			auto att = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_attack");
			CollisionChecker& col = CollisionChecker::GetSingleton();
            SpriteManager& manager = SpriteManager::GetSingleton();
            Sprite* sprite;
            int r = rand() % 3;
            if (r == 0) {
                sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "blue_pot_default", &drops_staflos, layer);
                col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_blue_pot_action);
            }
            else if (r == 1) {
                sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "red_pot_default", &drops_staflos, layer);
                col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_red_pot_action);
            }
            else {
                sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "points_default", &drops_staflos, layer);
                col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_big_point_action);
            }
            if (sprite != nullptr) {
                SpriteManager::GetSingleton().AddtoMap("drops", sprite);
				SpriteManager::GetSingleton().AddforDisplay("drops", sprite->GetTypeId());
                sprite->Move(0, 1);
            }
			g->Destroy();
			mv->Stop();
			dmg->Stop();
			att->Stop();
			att->Destroy();
			mv->Destroy();
			dmg->Destroy();
			

		}
	);
}


void init_staflos_animators(TileLayer *layer) {
	auto staflos = SpriteManager::GetSingleton().GetTypeList("Staflos");
	FrameRangeAnimation* staflos_move = new FrameRangeAnimation("staflos", 0, 1, 6, 5, 0, 80);
	FrameRangeAnimation* staflos_attack = new FrameRangeAnimation("staflos.attack", 0, 2, 3, 5, 0, 100);
	MovingAnimation* damage_an = new MovingAnimation("staflos.dmg", 2, 5, 0, 100);
	FrameRangeAnimation* fr_death = new FrameRangeAnimation("staflos.death", 0, 5, 1, 0, 0, 100);


	for (auto& g :staflos) {

		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId() + "_move", (FrameRangeAnimation*)staflos_move->Clone());
		FrameRangeAnimator* att = new FrameRangeAnimator(g->GetTypeId() + "_attack",(FrameRangeAnimation*)staflos_attack->Clone());

		MovingAnimator* damage_animator = new MovingAnimator(g->GetTypeId() + "_damage", (MovingAnimation*)damage_an->Clone());
		FrameRangeAnimator* death = new FrameRangeAnimator(g->GetTypeId() + "_death", (FrameRangeAnimation*)fr_death->Clone());


		g->SetVisibility(false);
		mv->SetOnAction(staflos_action(g,layer));
		mv->SetOnStart(staflos_start(g));
		mv->SetOnFinish(staflos_finish(g));

		att->SetOnAction(staflos_attack_action(g, layer));
		att->SetOnStart(staflos_attack_start(g));
		att->SetOnFinish(staflos_attack_finish(g));

		damage_animator->SetOnAction(damage_animator->generic_animator_action(g));
		damage_animator->SetOnStart(staflos_damage_start(g,mv));
		damage_animator->SetOnFinish(staflos_damage_finish(g));

		death->SetOnAction(staflos_death_action(g));
		death->SetOnStart(staflos_death_start(g));
		death->SetOnFinish(staflos_death_finish(g,layer));
	}
	
}


void init_staflos(TileLayer* layer){
	init_staflos_animators(layer);
}