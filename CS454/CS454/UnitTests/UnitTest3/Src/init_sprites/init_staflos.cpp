#include "../../Include/initAnimationsSprites.h"

Animator::OnStart staflos_attack_start(Sprite* s) {

	return ([s](Animator* anim)
		{
			generic_start(anim);
			s->ChangeFilm("Staflos.attack.right");
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
			s->ChangeFilm("Staflos.walk.right");
		}
	);
}

Animator::OnFinish staflos_finish(Sprite* g) {
	return ([g](Animator* anim)
		{

			generic_stop(anim);
			auto att = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_attack");
			if (att->HasFinished())
				att->Start(GetSystemTime());
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




void init_staflos_animators(TileLayer *layer) {
	auto staflos = SpriteManager::GetSingleton().GetTypeList("Staflos");
	FrameRangeAnimation* staflos_move = new FrameRangeAnimation("staflos", 0, 1, 5, -5, 0, 150);
	FrameRangeAnimation* staflos_attack = new FrameRangeAnimation("staflos.attack", 0, 2, 3, 5, 0, 150);
	for (auto& g :staflos) {

		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId() + "_move", (FrameRangeAnimation*)staflos_move->Clone());
		FrameRangeAnimator* att = new FrameRangeAnimator(g->GetTypeId() + "_attack",(FrameRangeAnimation*)staflos_attack->Clone());

		mv->SetOnAction(staflos_action(g,layer));
		mv->SetOnStart(staflos_start(g));
		mv->SetOnFinish(staflos_finish(g));

		att->SetOnAction(staflos_attack_action(g, layer));
		att->SetOnStart(staflos_attack_start(g));
		att->SetOnFinish(staflos_attack_finish(g));
	}
	
}


void init_staflos(TileLayer* layer){
	init_staflos_animators(layer);
}