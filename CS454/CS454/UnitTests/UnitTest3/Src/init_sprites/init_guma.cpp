
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"

Animator::OnStart proj_start( Sprite* s) {

	return ([s](Animator* anim) {

		SpriteManager::GetSingleton().AddforDisplay(s);
		generic_start(anim);
		});

}

Animator::OnFinish proj_finish( Sprite* s) {

	return ([s](Animator* anim) {

		//generic_stop(anim);
		CollisionChecker::GetSingleton().Cancel(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), s);
		s->Destroy();
		anim->Stop();
		generic_stop(anim);
		//animator->Stop();
		//const_cast<FrameRangeAnimation&>(animator->GetAnimation()).Destroy();
		anim->Destroy();

		});
}


void init_projectile(Sprite* proj, FrameRangeAnimator* animator) {

	animator->SetOnAction(animator->generic_animator_action(proj));
	animator->SetOnStart(proj_start( proj));
	animator->SetOnFinish(proj_finish(proj));

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

void proj_collission(Sprite *s1,Sprite *s2)
{
	pr_info("proj colli");
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
			CollisionChecker::GetSingleton().Register(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), sp_proj, proj_collission);
			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}



Animator::OnStart guma_damage_start( Sprite* g,FrameRangeAnimator *mv) {

	return ([g,mv](Animator* anim)
		{
			mv->Stop();
			CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(),"Guma")->setHit(true);
			auto film = g->GetFilm()->GetId();
			if (film == "Guma_left")
				((MovingAnimator*)anim)->SetDx(10);
			else
				((MovingAnimator*)anim)->SetDx(-10);
			
			generic_start(anim);
		}
	);
}

Animator::OnFinish guma_damage_finish( Sprite* g) {
	return ([g](Animator* anim)
		{
			
			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Guma");
			
			generic_stop(anim);
			if (c->is_Hit()) {
				c->setHit(false);
				AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move")->Start(GetSystemTime());
			}
		}
	);
}




void init_guma_animators(TileLayer* layer) {
	auto Gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	FrameRangeAnimation* fr_guma = new FrameRangeAnimation("guma", 0, 3, 0, 5, 0, 80);
	FrameRangeAnimation* proj = new FrameRangeAnimation("proj", 0, 3, 15, 5, 0, 65);

	MovingAnimation* damage_an = new MovingAnimation("guma.dmg", 2, 5, 0, 100);

	for (auto& g : Gumas) {
		
		MovingAnimator* damage_animator = new MovingAnimator(g->GetTypeId() + "_damage", (MovingAnimation*)damage_an->Clone());
		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId()+"_move", (FrameRangeAnimation*)fr_guma->Clone());
		mv->SetOnAction(guma_action((FrameRangeAnimation*)proj->Clone(),g,layer));
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(generic_stop);

		damage_animator->SetOnAction(damage_animator->generic_animator_action(g));
		damage_animator->SetOnStart(guma_damage_start(g,mv));
		damage_animator->SetOnFinish(guma_damage_finish(g));

	}
	
	fr_guma->Destroy();
	proj->Destroy();
	//AnimatorManager::GetSingleton().Get_by_Id("Guma_move")->Start(GetSystemTime());
}

void init_guma(TileLayer* layer){
	init_guma_animators(layer);
}