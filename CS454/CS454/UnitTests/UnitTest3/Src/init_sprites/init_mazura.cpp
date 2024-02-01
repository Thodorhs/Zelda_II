#pragma once
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/Link/Link.h"
#include "../../Include/CreateSprite.h"

Animator::OnStart mazura_move_start(Sprite *m) {

	return ([ m](Animator* anim)
		{
			Link::GetSingleton().setOnBoss(true);
			auto c = CharacterManager::GetSingleton().Get_by_Id("Mazura", "Mazura");
			if (!c->is_Alive())
				return;
			generic_start(anim);
		}
	);
}

Animator::OnFinish mazura_move_finish( Sprite* g) {
	return ([g](Animator* anim)
		{

			generic_stop(anim);
		//	AnimatorManager::GetSingleton().Get_by_Id("Mazura_attack")->Start(GetSystemTime());
		}
	);
}


Animator::OnAction mazura_move_action(Sprite* g) {


	return ([g](Animator* animator, const Animation& anim)
		{
		

			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
			
		}
	);
}


Animator::OnStart mazura_attack_start( Sprite* g) {

	return ([g](Animator* anim)
		{
			auto c = CharacterManager::GetSingleton().Get_by_Id("Mazura", "Mazura");
			if (!c->is_Alive())
				return;
			auto* an = (FrameRangeAnimator*)anim;
			auto dx = an->GetDx();
			if (dx > 0)
				g->ChangeFilm("Mazura_attack_right");
			else
				g->ChangeFilm("Mazura_attack_left");

			generic_start(anim);
		}
	);
}

Animator::OnFinish mazura_attack_finish(Sprite* g) {
	return ([g](Animator* anim)
		{

			generic_stop(anim);
		}
	);
}


Animator::OnAction mazura_attack_action(Sprite* g) {


	return ([g](Animator* animator, const Animation& anim)
		{


			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}





Animator::OnStart mazura_charge_start(Sprite* g) {

	return ([g](Animator* anim)
		{
			auto c = CharacterManager::GetSingleton().Get_by_Id("Mazura", "Mazura");
			if (!c->is_Alive())
				return;
			SoundManager::get_singleton().play_sfx("AOL_Fire.wav", 0, 2);
			auto* an = (FrameRangeAnimator*)anim;
			auto dx = an->GetDx();
			if (dx > 0)
				g->ChangeFilm("Mazura_charge_right");
			else
				g->ChangeFilm("Mazura_charge_left");

			generic_start(anim);
		}
	);
}

Animator::OnFinish mazura_charge_finish(Sprite* g) {
	return ([g](Animator* anim)
		{
			auto film = g->Get_film_id();

			if (film == "Mazura_charge_right")
				g->ChangeFilm("Mazura_walk_right");
			else
				g->ChangeFilm("Mazura_walk_left");
			generic_stop(anim);
		}
	);
}


Animator::OnAction mazura_charge_action(Sprite* g) {


	return ([g](Animator* animator, const Animation& anim)
		{


			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}

Animator::OnStart mazura_death_start(Sprite* g,FrameRangeAnimator* charge,FrameRangeAnimator* attack,FrameRangeAnimator* move) {

	return ([g,charge,attack,move](Animator* anim)
		{
			SoundManager::get_singleton().play_sfx("AOL_KillBoss.wav", 0, 2);
			g->ChangeFilm("death_default");
			AnimatorManager::GetSingleton().Get_by_Id("Mazura_damage")->Stop();
			
			charge->Stop();
			attack->Stop();
			move->Stop();
			generic_start(anim);
		}
	);
}

Animator::OnFinish mazura_death_finish(Sprite* g, FrameRangeAnimator* charge, FrameRangeAnimator* attack, FrameRangeAnimator* move,TileLayer *layer) {
	return ([g, charge, attack, move,layer](Animator* anim)
		{

			SoundManager::get_singleton().pause_music();
			SoundManager::get_singleton().play_sfx("AOL_Item_Drop.wav", 0, 2);
			SoundManager::get_singleton().play_music("end.mp3", 2);
			auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
			CollisionChecker::GetSingleton().Cancel(link, g);
			CollisionChecker& col = CollisionChecker::GetSingleton();
			SpriteManager& manager = SpriteManager::GetSingleton();
			Sprite* sprite = nullptr;
			sprite = create_drop_boss(g, AnimationFilmHolder::getInstance(), "key_default", layer);
			col.Register(manager.Get_sprite_by_id("Link"), sprite, key_action_boss);
			if (sprite != nullptr) {
				SpriteManager::GetSingleton().AddtoMap("drops", sprite);
				SpriteManager::GetSingleton().AddforDisplay("drops", sprite->GetTypeId());
				sprite->Move(0, 1);
			}
			charge->Stop();
			attack->Stop();
			move->Stop();
			charge->Destroy();
			attack->Destroy();
			move->Destroy();
			g->Destroy();
			AnimatorManager::GetSingleton().Get_by_Id("Mazura_damage")->Destroy();
			generic_stop(anim);
		}
	);
}



Animator::OnStart mazura_damage_start(Sprite* g) {

	return ([g](Animator* anim)
		{
			SoundManager::get_singleton().play_sfx("AOL_Sword_Hit.wav", 0, 2);
			auto c = CharacterManager::GetSingleton().Get_by_Id("Mazura","Mazura");
			c->setHit(true);
			auto hp = c->get_health() - Link::GetSingleton().get_dps();
			c->set_health(hp);
			if (hp <= 0) {
				AnimatorManager::GetSingleton().Get_by_Id("Mazura_death")->Start(GetSystemTime());
				g->GetGravityHandler().set_gravity_addicted(false);
				g->setCanMove(false);
			}
			else
				generic_start(anim);
		}
	);
}

Animator::OnFinish mazura_damage_finish(Sprite* g) {
	return ([g](Animator* anim)
		{
			auto c = CharacterManager::GetSingleton().Get_by_Id("Mazura", "Mazura");
			if (c->is_Alive() && c->is_Hit())
				c->setHit(false);
			generic_stop(anim);
		}
	);
}




Animator::OnAction mazura_death_action(Sprite* g) {


	return ([g](Animator* animator, const Animation& anim)
		{


			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}









void init_mazura_animators(TileLayer* layer) {
	auto mazura = SpriteManager::GetSingleton().GetTypeList("Mazura").begin();

	FrameRangeAnimation* maz_move = new FrameRangeAnimation("maz", 0, 2, 1, 5, 0, 200);
	FrameRangeAnimation* maz_attack = new FrameRangeAnimation("maz.attack", 0, 3, 1, 1, 0, 150);
	MovingAnimation* maz_damage = new MovingAnimation("maz.damage", 1, 0, 0, 200);



	FrameRangeAnimation* charge_an = new FrameRangeAnimation("maz.ch",0,30, 1, 20, 0, 80);

	FrameRangeAnimator* charge = new FrameRangeAnimator("Mazura_charge", charge_an);
	
	FrameRangeAnimation* fr_death = new FrameRangeAnimation("maz.death", 0, 5, 3, 0, 0, 100);

	MovingAnimator* damage = new MovingAnimator("Mazura_damage", maz_damage);


	FrameRangeAnimator* mv = new FrameRangeAnimator("Mazura_move", maz_move);
	FrameRangeAnimator* att = new FrameRangeAnimator("Mazura_attack", maz_attack);

	
	FrameRangeAnimator* death = new FrameRangeAnimator( "Mazura_death", fr_death);


	mv->SetOnAction(mazura_move_action(*mazura));
	mv->SetOnStart(mazura_move_start(*mazura));
	mv->SetOnFinish(mazura_move_finish(*mazura));

	att->SetOnAction(mazura_attack_action(*mazura));
	att->SetOnStart(mazura_attack_start(*mazura));
	att->SetOnFinish(mazura_attack_finish(*mazura));

	charge->SetOnAction(mazura_charge_action(*mazura));
	charge->SetOnStart(mazura_charge_start(*mazura));
	charge->SetOnFinish(mazura_charge_finish(*mazura));

	death->SetOnAction(mazura_death_action(*mazura));
	death->SetOnStart(mazura_death_start(*mazura,charge,att,mv));
	death->SetOnFinish(mazura_death_finish(*mazura,charge,att,mv,layer));

	damage->SetOnAction(damage->generic_animator_action(*mazura));
	damage->SetOnStart(mazura_damage_start(*mazura));
	damage->SetOnFinish(mazura_damage_finish(*mazura));

}



void init_mazura(TileLayer* layer) {
	init_mazura_animators(layer);

}