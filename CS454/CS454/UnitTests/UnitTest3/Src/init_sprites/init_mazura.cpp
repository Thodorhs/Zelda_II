#pragma once
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/Link/Link.h"
#include "../../Include/CreateSprite.h"

Animator::OnStart mazura_move_start(Sprite *m) {

	return ([ m](Animator* anim)
		{

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










void init_mazura_animators(TileLayer* layer) {
	auto mazura = SpriteManager::GetSingleton().GetTypeList("Mazura").begin();

	FrameRangeAnimation* maz_move = new FrameRangeAnimation("maz", 0, 2, 1, 5, 0, 200);
	FrameRangeAnimation* maz_attack = new FrameRangeAnimation("maz.attack", 0, 3, 1, 1, 0, 150);

	FrameRangeAnimation* charge_an = new FrameRangeAnimation("maz.ch",0,30, 1, 20, 0, 80);

	FrameRangeAnimator* charge = new FrameRangeAnimator("Mazura_charge", charge_an);
	
	FrameRangeAnimation* fr_death = new FrameRangeAnimation("maz.death", 0, 5, 1, 0, 0, 100);




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

}



void init_mazura(TileLayer* layer) {
	init_mazura_animators(layer);

}