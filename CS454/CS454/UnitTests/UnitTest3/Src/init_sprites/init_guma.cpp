
#include "../../../../Engine/Include/Animations/MovingPathAnimation.h"
#include "../../../../Engine/Include/Animators/MovingPathAnimator.h"
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/Characters/Guma.h"
#include "../../Include/Link/Link.h"

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
		anim->Destroy();

		});
}


void init_projectile(Sprite* proj, MovingPathAnimator* animator) {

	animator->SetOnAction(animator->generic_animator_action(proj));
	animator->SetOnStart(proj_start( proj));
	animator->SetOnFinish(proj_finish(proj));

}

int x = 0;
Sprite* create_proj_sprite(Sprite* guma, AnimationFilmHolder& holder) {
	x++;
	return new Sprite(guma->GetBox().x+20, guma->GetBox().y, const_cast<AnimationFilm*>(holder.GetFilm(get_sprite_initial_film("Guma_proj"))), guma->GetTypeId() + "_proj"+std::to_string(x));
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
{	if(Link::GetSingleton().can_hit(GetSystemTime(), 500)){
		Link::GetSingleton().damage(Link::GetSingleton().getdif()-2);
		AnimatorManager::GetSingleton().Get_by_Id("Link_damage")->Start(GetSystemTime());
		pr_info("proj collission");
	}
}

timestamp_t lasttime;

Animator::OnAction guma_action(MovingPathAnimation* proj_anim, Sprite* g, TileLayer* layer) {
	

	return ([proj_anim, layer, g](Animator* animator, const Animation& anim)
		{
			auto c = ((Guma*)CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Guma"));
			unsigned rate = 1;
			if (c)
				rate = c->GetRate();
			if (GetSystemTime() > lasttime + 500) {
				for (int i = 0; i < rate; i++) {
					MovingPathAnimator* proj_an = new MovingPathAnimator(g->GetTypeId() + "_proj", proj_anim);
					Sprite* sp_proj = create_proj_sprite(g, AnimationFilmHolder::getInstance());


					sp_proj->SetHasDirectMotion(true);

					sp_proj->SetMover(sp_proj->MakeSpriteGridLayerMover(layer, sp_proj));
					SpriteManager::GetSingleton().AddtoMap("projectile", sp_proj);
					init_projectile(sp_proj, proj_an);
					proj_an->Start(GetSystemTime());
					CollisionChecker::GetSingleton().Register(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), sp_proj, proj_collission);
				}
				lasttime = GetSystemTime();
			}
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

	MovingAnimation* damage_an = new MovingAnimation("guma.dmg", 2, 5, 0, 100);

	std::vector<PathEntry> my_path;
	my_path.push_back(PathEntry(0,-10,0,100 ));
	my_path.push_back(PathEntry(-4,-11,1,100 ));
	my_path.push_back(PathEntry(-5,-12,2,100 ));
	my_path.push_back(PathEntry(-6,-13,3,100 ));
	my_path.push_back(PathEntry(-6,-14,0,100 ));
	my_path.push_back(PathEntry(-7,-10,1,120 ));
	my_path.push_back(PathEntry(-7,-8,2,130 ));
	my_path.push_back(PathEntry(-8,-6,3,130 ));
	my_path.push_back(PathEntry(-10,5,0,100 ));
	my_path.push_back(PathEntry(-10,5,1,100 ));
	my_path.push_back(PathEntry(-8,10,2,100 ));
	my_path.push_back(PathEntry(-8,10,3,100 ));
	my_path.push_back(PathEntry(-8,10,0,100 ));
	my_path.push_back(PathEntry(-8,10,1,80 ));
	my_path.push_back(PathEntry(-3,12,2,80 ));
	my_path.push_back(PathEntry(-3,13,3,70 ));
	my_path.push_back(PathEntry(-3,14,0,70 ));
	my_path.push_back(PathEntry(-2,15,1,70 ));
	my_path.push_back(PathEntry(-1,16,2,60 ));
	my_path.push_back(PathEntry(-1,16,3,60 ));


	MovingPathAnimation *path = new MovingPathAnimation("path", my_path, my_path.size());



	for (auto& g : Gumas) {
		
		MovingAnimator* damage_animator = new MovingAnimator(g->GetTypeId() + "_damage", (MovingAnimation*)damage_an->Clone());
		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId()+"_move", (FrameRangeAnimation*)fr_guma->Clone());
		mv->SetOnAction(guma_action((MovingPathAnimation*)path->Clone(),g,layer));
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(generic_stop);

		damage_animator->SetOnAction(damage_animator->generic_animator_action(g));
		damage_animator->SetOnStart(guma_damage_start(g,mv));
		damage_animator->SetOnFinish(guma_damage_finish(g));

	}
	
	fr_guma->Destroy();
	
	//AnimatorManager::GetSingleton().Get_by_Id("Guma_move")->Start(GetSystemTime());
}

void init_guma(TileLayer* layer){
	init_guma_animators(layer);
}