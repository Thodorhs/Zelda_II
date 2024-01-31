#pragma once
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/Link/Link.h"
#include "../../Include/CreateSprite.h"


Animator::OnStart bot_jump_start(Sprite *b,MovingAnimator* fall,FrameRangeAnimator *move,int scale) {
	
	return ([b,fall,move,scale](Animator* anim)
		{
			if (!CharacterManager::GetSingleton().Get_by_Id(b->GetTypeId(), "Palace_bot")->is_Alive())
				return;
			//b->Move(5, 0);
			if (!fall->HasFinished()) {
				dynamic_cast<MovingAnimator*>(anim)->SetDy(0);
				dynamic_cast<MovingAnimator*>(anim)->SetDx(0);
			}
			else {
				dynamic_cast<MovingAnimator*>(anim)->SetDy(-scale * 8);
				dynamic_cast<MovingAnimator*>(anim)->SetDx(dynamic_cast<MovingAnimator*>(anim)->GetDx());
				dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(b->GetTypeId() + "_falling"))->SetDx(dynamic_cast<MovingAnimator*>(anim)->GetDx());
			}
			generic_start(anim);
		}
	);
}


Animator::OnFinish bot_jump_stop(FrameRangeAnimator *move,Sprite *b) {
	return ([move,b](Animator* anim)
		{
			auto c = CharacterManager::GetSingleton().Get_by_Id(b->GetTypeId(), "Palace_bot");
			if (c && c->is_Alive()) {
				move->Start(GetSystemTime());
			}
			generic_stop(anim);
		}
	);
}


Animator::OnFinish bot_move_stop(MovingAnimator *jump,Sprite* s) {
	return ([jump,s](Animator* anim)
		{
			auto c = CharacterManager::GetSingleton().Get_by_Id(s->GetTypeId(), "Palace_bot");
			if (c && c->is_Alive()) {
				jump->Start(GetSystemTime());
			}
			
			generic_stop(anim);
		}
	);
}



Animator::OnStart bot_damage_finish(Sprite* g) {

	return ([g](Animator* anim)
		{
			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Palace_bot");

			generic_stop(anim);
			if (!c->is_Alive())
				return;
			g->GetGravityHandler().set_gravity_addicted(true);
			if (c->is_Hit()) {
				c->setHit(false);
				AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move")->Start(GetSystemTime());
			}
			
		}
	);
}

Animator::OnAction bot_death_action(Sprite* g) {
	return ([g](Animator* animator, const Animation& anim)
		{
			SoundManager::get_singleton().play_sfx("AOL_Kill.wav", 0, 2);
			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}



Animator::OnStart bot_damage_start(Sprite* g, MovingAnimator* mv,FrameRangeAnimator *fr) {

	return ([g, mv,fr](Animator* anim)
		{
			SoundManager::get_singleton().play_sfx("AOL_Sword_Hit.wav", 0, 2);
			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Palace_bot");
			c->setHit(true);
			auto film = g->GetFilm()->GetId();
			auto health = c->get_health() - Link::GetSingleton().get_dps();
			//g->GetGravityHandler().set_gravity_addicted(false);
			c->set_health(health);
			//fr->Stop();
			//mv->Stop();
			if (health <= 0) {
				AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_death")->Start(GetSystemTime());
			}
			else {
				generic_start(anim);
			}
		}
	);
}



Animator::OnStart bot_death_start(Sprite* g) {

	return ([g](Animator* anim)
		{
			Link::GetSingleton().addPoints(10);
			auto mv = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move");
			auto dmg = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_damage");
			auto jmp = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_jump");
			mv->Stop();
			dmg->Stop();
			jmp->Stop();
			g->ChangeFilm("death_bot");
			g->GetGravityHandler().set_gravity_addicted(false);
			
			//mv->Destroy();
			//dmg->Destroy();
			generic_start(anim);
			
		}
	);
}

int drops_bot = 0;
Animator::OnFinish bot_death_finish(Sprite* g, TileLayer* layer) {

	return ([g, layer](Animator* anim)
		{

			CharacterManager::GetSingleton().Erase(g->GetTypeId(), "Palace_bot");
			CollisionChecker::GetSingleton().Cancel(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), g);
			generic_stop(anim);
			anim->Destroy();
			auto mv = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move");
			auto dmg = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_damage");
			auto jmp = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_jump");
			CollisionChecker& col = CollisionChecker::GetSingleton();
			SpriteManager& manager = SpriteManager::GetSingleton();
			Sprite* sprite = nullptr;
			int r = rand() % 23;
			if (r == 0) {
				sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "blue_pot_default", &drops_bot, layer);
				col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_blue_pot_action);
			}
			else if (r == 6) {
				sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "red_pot_default", &drops_bot, layer);
				col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_red_pot_action);
			}
			else if(r == 15) {
				sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "points_default", &drops_bot, layer);
				col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_point_action);
			}
			if (sprite != nullptr) {
				SoundManager::get_singleton().play_sfx("AOL_Item_Drop.wav", 0, 2);
				SpriteManager::GetSingleton().AddtoMap("drops", sprite);
				SpriteManager::GetSingleton().AddforDisplay("drops", sprite->GetTypeId());
				sprite->Move(0, 1);

				
			}
			g->Destroy();
			mv->Stop();
			dmg->Stop();
			jmp->Stop();
			mv->Destroy();
			dmg->Destroy();
			jmp->Destroy();
		});
}


void init_bot_animators(TileLayer* layer) {
	auto bots = SpriteManager::GetSingleton().GetTypeList("Palace_bot");
	FrameRangeAnimation* fr_bot = new FrameRangeAnimation("bot", 0, 1, 5, 0, 0, 200);
	MovingAnimation* bot_jump = new MovingAnimation("bot.jump", 5, 10, -layer->get_scale()*8, 45);
	FrameRangeAnimation* fr_death = new FrameRangeAnimation("bot.death", 0, 5, 1, 0, 0, 100);
	MovingAnimation* damage_an = new MovingAnimation("staflos.dmg", 1, 0, 0, 100);

	for (auto& b : bots) {
		MovingAnimator* damage_animator = new MovingAnimator(b->GetTypeId() + "_damage", (MovingAnimation*)damage_an->Clone());
		FrameRangeAnimator* death = new FrameRangeAnimator(b->GetTypeId() + "_death", (FrameRangeAnimation*)fr_death->Clone());
		MovingAnimation* mv_an_clone = (MovingAnimation*)bot_jump->Clone();
		FrameRangeAnimation* fr_bot_clone = (FrameRangeAnimation*)fr_bot->Clone();
		MovingAnimator* bot_jump_an = new MovingAnimator(b->GetTypeId() + "_jump",mv_an_clone);
		FrameRangeAnimator* mv = new FrameRangeAnimator(b->GetTypeId() + "_move",fr_bot_clone);
		mv->SetOnAction(mv->generic_animator_action(b));
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(bot_move_stop(bot_jump_an,b));

		MovingAnimator* fall = dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(b->GetTypeId() + "_falling"));
		fall->SetDelay(80);
		fall->SetDx(8);

		bot_jump_an->SetOnAction(bot_jump_an->generic_animator_action(b));
		bot_jump_an->SetOnStart(bot_jump_start(b,fall,mv,layer->get_scale()));
		bot_jump_an->SetOnFinish(bot_jump_stop(mv,b));	

		death->SetOnAction(death->generic_animator_action(b));
		death->SetOnStart(bot_death_start(b));
		death->SetOnFinish(bot_death_finish(b,layer));


		damage_animator->SetOnAction(damage_animator->generic_animator_action(b));
		damage_animator->SetOnStart(bot_damage_start(b,bot_jump_an,mv));
		damage_animator->SetOnFinish(bot_damage_finish(b));
	}
	fr_bot->Destroy();
	bot_jump->Destroy();
	//AnimatorManager::GetSingleton().Get_by_Id("Palace_bot_move")->Start(GetSystemTime());
	//AnimatorManager::GetSingleton().Get_by_Id("Palace_bot_jump")->Start(GetSystemTime());
}

void init_bot(TileLayer* layer) {
	init_bot_animators(layer);
}