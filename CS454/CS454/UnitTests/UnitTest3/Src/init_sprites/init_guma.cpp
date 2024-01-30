#pragma once
#include "../../../../Engine/Include/Animations/MovingPathAnimation.h"
#include "../../../../Engine/Include/Animators/MovingPathAnimator.h"
#include "../../Include/initAnimationsSprites.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../Include/Characters/Guma.h"
#include "../../Include/Link/Link.h"
#include "../../Include/CreateSprite.h"
#include "../../Include/SoundManager/SoundManager.h"

std::vector<PathEntry> left_path;
std::vector<PathEntry> right_path;

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

			if (!CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Guma")->is_Alive())
				return;
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
		if (s1->GetFilm()->GetId() == "Link.Crouch.right" && (s2->GetBox().x >= s1->GetBox().x)) {
			SoundManager::get_singleton().play_sfx("AOL_Deflect.wav", 0, 2);
			pr_info("parry");
			return;
		}
		else if (s1->GetFilm()->GetId() == "Link.Crouch.left" && (s2->GetBox().x <= s1->GetBox().x)) {
			SoundManager::get_singleton().play_sfx("AOL_Deflect.wav", 0, 2);
			pr_info("parry");
			return;
		}
		Link::GetSingleton().damage(Link::GetSingleton().getdif()-2);
		AnimatorManager::GetSingleton().Get_by_Id("Link_damage")->Start(GetSystemTime());
		pr_info("proj collission");
	}
}

timestamp_t lasttime;
std::string prev_guma_flm;

Animator::OnAction guma_action(MovingPathAnimation* proj_anim, Sprite* g, TileLayer* layer) {
	

	return ([proj_anim, layer, g](Animator* animator, const Animation& anim)
		{
			auto c = ((Guma*)CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Guma"));
			unsigned rate = 1;

			auto film = g->GetFilm()->GetId();
			
			if (GetSystemTime() > lasttime+83) {
				
				if(rand() % 3 == 1) {
					MovingPathAnimator* proj_an = new MovingPathAnimator(g->GetTypeId() + "_proj", proj_anim);
					Sprite* sp_proj = create_proj_sprite(g, AnimationFilmHolder::getInstance());
					if (film == "Guma_right")
					{
						proj_anim->SetPath(right_path);
					}
					else
					{
						proj_anim->SetPath(left_path);
					}

					sp_proj->SetHasDirectMotion(true);

					sp_proj->SetMover(sp_proj->MakeSpriteGridLayerMover(layer, sp_proj));
					SpriteManager::GetSingleton().AddtoMap("projectile", sp_proj);
					init_projectile(sp_proj, proj_an);
					proj_an->Start(GetSystemTime());
					CollisionChecker::GetSingleton().Register(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), sp_proj, proj_collission);
				}
			}
			lasttime = GetSystemTime();
			
			FrameRange_Action_noSet(g, animator, (const FrameRangeAnimation&)anim);
		}
	);
}



Animator::OnStart guma_damage_start( Sprite* g,FrameRangeAnimator *mv) {

	return ([g,mv](Animator* anim)
		{
			SoundManager::get_singleton().play_sfx("AOL_Sword_Hit.wav", 0, 2);
			mv->Stop();
			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Guma");
			c->setHit(true);
			auto film = g->GetFilm()->GetId();
			auto health = c->get_health() - Link::GetSingleton().get_dps();
			c->set_health(health);
			if (health <= 0) {
				AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_death")->Start(GetSystemTime());
			}
			else {
				if (film == "Guma_left")
					((MovingAnimator*)anim)->SetDx(10);
				else
					((MovingAnimator*)anim)->SetDx(-10);

				generic_start(anim);
			}
		}
	);
}

Animator::OnFinish guma_damage_finish( Sprite* g) {
	return ([g](Animator* anim)
		{
			
			auto c = CharacterManager::GetSingleton().Get_by_Id(g->GetTypeId(), "Guma");
			
			generic_stop(anim);
			if (!c->is_Alive())
				return;
			if (c->is_Hit() ) {
				c->setHit(false);
				AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move")->Start(GetSystemTime());
			}
		}
	);
}




int drops_guma = 0;
Animator::OnStart guma_death_start(Sprite* g,TileLayer *layer) {

	return ([g,layer](Animator* anim)
		{
			SoundManager::get_singleton().play_sfx("AOL_Kill.wav", 0, 2);
			Link::GetSingleton().addPoints(50);
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

Animator::OnFinish guma_death_finish(Sprite* g,TileLayer *layer) {
	return ([g,layer](Animator* anim)
		{

			CharacterManager::GetSingleton().Erase(g->GetTypeId(), "Guma");
			CollisionChecker::GetSingleton().Cancel(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), g);
			generic_stop(anim);
			anim->Destroy();
			auto mv = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_move");
			auto dmg = AnimatorManager::GetSingleton().Get_by_Id(g->GetTypeId() + "_damage");
			CollisionChecker& col = CollisionChecker::GetSingleton();
			SpriteManager& manager = SpriteManager::GetSingleton();
			Sprite* sprite = nullptr;
			int r = rand() % 23;
			if (r == 0) {
				sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "blue_pot_default", &drops_guma, layer);
				col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_blue_pot_action);
			}
			else if (r == 12) {
				sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "red_pot_default", &drops_guma, layer);
				col.Register(manager.Get_sprite_by_id("Link"), sprite, drop_red_pot_action);
			}
			else if (r == 18) {
				sprite = create_drop_sprite(g, AnimationFilmHolder::getInstance(), "points_default", &drops_guma, layer);
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
			mv->Destroy();
			dmg->Destroy();
			
		}
	);
}









void init_guma_animators(TileLayer* layer) {
	auto Gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	FrameRangeAnimation* fr_guma = new FrameRangeAnimation("guma", 0, 3, 0, 5, 0, 80);

	MovingAnimation* damage_an = new MovingAnimation("guma.dmg", 2, 5, 0, 100);

	
	left_path.push_back(PathEntry(0,-10,0,100 ));
	left_path.push_back(PathEntry(-4,-11,1,100 ));
	left_path.push_back(PathEntry(-5,-12,2,100 ));
	left_path.push_back(PathEntry(-6,-13,3,100 ));
	left_path.push_back(PathEntry(-6,-14,0,100 ));
	left_path.push_back(PathEntry(-7,-10,1,120 ));
	left_path.push_back(PathEntry(-7,-8,2,130 ));
	left_path.push_back(PathEntry(-8,-6,3,130 ));
	left_path.push_back(PathEntry(-10,5,0,100 ));
	left_path.push_back(PathEntry(-10,5,1,100 ));
	left_path.push_back(PathEntry(-8,10,2,100 ));
	left_path.push_back(PathEntry(-8,10,3,100 ));
	left_path.push_back(PathEntry(-8,10,0,100 ));
	left_path.push_back(PathEntry(-8,10,1,80 ));
	left_path.push_back(PathEntry(-3,12,2,80 ));
	left_path.push_back(PathEntry(-3,13,3,70 ));
	left_path.push_back(PathEntry(-3,14,0,70 ));
	left_path.push_back(PathEntry(-2,15,1,70 ));
	left_path.push_back(PathEntry(-1,16,2,60 ));
	left_path.push_back(PathEntry(-1,16,3,60 ));

	for (auto& it : left_path)
		right_path.push_back(it);
	
	for(int i =0; i<left_path.size(); i++)
	{
		right_path[i].dx = -right_path[i].dx;
	}


	MovingPathAnimation *path = new MovingPathAnimation("path", left_path, left_path.size());

	FrameRangeAnimation* fr_death = new FrameRangeAnimation("guma.death", 0, 5, 1, 0, 0, 100);

	for (auto& g : Gumas) {
		
		MovingAnimator* damage_animator = new MovingAnimator(g->GetTypeId() + "_damage", (MovingAnimation*)damage_an->Clone());
		
		FrameRangeAnimator* death = new FrameRangeAnimator(g->GetTypeId() + "_death", (FrameRangeAnimation*)fr_death->Clone());

		FrameRangeAnimator* mv = new FrameRangeAnimator(g->GetTypeId() + "_move", (FrameRangeAnimation*)fr_guma->Clone());

		mv->SetOnAction(guma_action((MovingPathAnimation*)path->Clone(),g,layer));
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(generic_stop);

		damage_animator->SetOnAction(damage_animator->generic_animator_action(g));
		damage_animator->SetOnStart(guma_damage_start(g,mv));
		damage_animator->SetOnFinish(guma_damage_finish(g));

		death->SetOnAction(death->generic_animator_action(g));
		death->SetOnStart(guma_death_start(g,layer));
		death->SetOnFinish(guma_death_finish(g,layer));

	}
	
	fr_guma->Destroy();
	
	//AnimatorManager::GetSingleton().Get_by_Id("Guma_move")->Start(GetSystemTime());
}

void init_guma(TileLayer* layer){
	init_guma_animators(layer);
}