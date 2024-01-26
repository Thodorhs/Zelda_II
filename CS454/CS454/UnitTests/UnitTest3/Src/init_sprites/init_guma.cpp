
#include "../../Include/initAnimationsSprites.h"

Animator::OnStart proj_start(FrameRangeAnimator* animator, Sprite* s) {

	return ([s](Animator* anim) {

		SpriteManager::GetSingleton().AddforDisplay(s);
		generic_start(anim);
		});

}

Animator::OnFinish proj_finish(FrameRangeAnimator* animator, Sprite* s) {

	return ([s,animator](Animator* anim) {
		
		s->Destroy();
		anim->Stop();
		generic_stop(anim);
		
		animator->Destroy();
		});
}


void init_projectile(Sprite* proj, FrameRangeAnimator* animator) {

	animator->SetOnAction(animator->generic_animator_action(proj));
	animator->SetOnStart(proj_start(animator, proj));
	animator->SetOnFinish(proj_finish(animator, proj));

}


Sprite* create_proj_sprite(Sprite* guma, AnimationFilmHolder& holder) {
	return new Sprite(guma->GetBox().x+20, guma->GetBox().y, const_cast<AnimationFilm*>(holder.GetFilm(get_sprite_initial_film("Guma_proj"))), guma->GetTypeId() + "_proj");
}




Animator::OnStart guma_start(Animator *animator,FrameRangeAnimation *proj_anim,Sprite *g,TileLayer *layer) {

	return ([proj_anim,g,layer](Animator *anim)
		{
		
			generic_start(anim);
		}
	);
}

Animator::OnFinish guma_finish(Animator *animator,FrameRangeAnimation *proj_anim,Sprite* g) {
	return ([g](Animator *anim)
		{
			
			generic_stop(anim);
		}
	);
}

Animator::OnAction guma_action(FrameRangeAnimation* proj_anim, Sprite* g, TileLayer* layer) {
	return ([proj_anim, layer, g](Animator* animator, const Animation& anim)
		{
			FrameRangeAnimator* proj_an = new FrameRangeAnimator(g->GetTypeId() + "_proj", proj_anim);
			Sprite* sp_proj = create_proj_sprite(g, AnimationFilmHolder::getInstance());
		

			sp_proj->SetHasDirectMotion(true);
			sp_proj->SetMover(sp_proj->MakeSpriteGridLayerMover(layer, sp_proj));
			SpriteManager::GetSingleton().AddtoMap("projectile", sp_proj);
			init_projectile(sp_proj, proj_an);
			proj_an->Start(GetSystemTime());
			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}



void init_guma_animators(TileLayer* layer) {
	auto Gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	FrameRangeAnimation* fr_guma = new FrameRangeAnimation("guma", 0, 3, 0, 5, 0, 150);
	FrameRangeAnimation* proj = new FrameRangeAnimation("proj", 0, 3, 10, 5, 0, 100);

	for (auto& g : Gumas) {
		

		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId()+"_move", fr_guma);
		mv->SetOnAction(guma_action(proj,g,layer));
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(generic_stop);
	}
	AnimatorManager::GetSingleton().Get_by_Id("Guma_move")->Start(GetSystemTime());
}

void init_guma(TileLayer* layer){
	init_guma_animators(layer);
}