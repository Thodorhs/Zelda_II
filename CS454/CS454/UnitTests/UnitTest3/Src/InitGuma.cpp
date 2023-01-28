#include "Initialise_characters.h"



void initialise_guma_films(GameCharacter* enemy) {
	AnimationFilm* enemy_film = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Guma"));
	enemy->set_film("id", enemy_film);
}

Sprite* initialise_guma_sprites(GameCharacter* character, GridLayer GameGrid) {
	Sprite* guma_sprite = new Sprite(guma_x, guma_y, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Guma")), "Guma");
	guma_sprite->SetMover(MakeSpriteGridLayerMover(&GameGrid, guma_sprite));
	guma_sprite->SetCombatSystem(320, 8);
	PrepareSpriteGravityHandler(&GameGrid, guma_sprite);


	guma_sprite->GetGravityHandler().gravityAddicted = true;
	guma_sprite->GetGravityHandler().SetOnStartFalling(
		[character]() {character->stop_animators();
	return; });
	guma_sprite->GetGravityHandler().SetOnStopFalling(
		[guma_sprite]() {
			guma_sprite->GetGravityHandler().isFalling = false;
	//std::cout << "called";
	guma_sprite->SetHasDirectMotion(false);
		});
	//guma_sprite->Move(1, 0);
	character->set_current(guma_sprite);
	character->set_id("Guma");


	return guma_sprite;
}


void initialise_guma_animations(Sprite* guma, GameCharacter* character) {
	MovingAnimator* move = new MovingAnimator();
	MovingAnimation* move_anim = new MovingAnimation("guma.move", 1, 0, 0, 50);
	FrameRangeAnimator* attack_move = new FrameRangeAnimator();
	FrameRangeAnimation* attack_move_animation = new FrameRangeAnimation("guma.attack", 0, 3, 10, 0, 0, 200);

	attack_move->SetOnAction([guma](Animator* animator, const Animation& anim) {
		FrameRange_Action(guma, animator, (const FrameRangeAnimation&)anim);
		});
	attack_move->SetOnStart([](Animator* animator) {});
	attack_move->SetOnFinish([](Animator* animator) {});


	character->set_animation("guma.move_animation", move_anim);
	character->set_animator("guma.move_animator", move);
	character->set_animation("guma.attack_move_animation", attack_move_animation);
	character->set_animator("guma.attack_move_animator", attack_move);
	character->set_current(guma);
	//attack_move->Start(attack_move_animation,GetSystemTime());
}

void init_projectile(Sprite* guma, GameCharacter* character) {
	MovingAnimator* proj_moving_animator;
	MovingAnimation* proj_moving_animation;
	FrameRangeAnimator* proj_fr_animator;
	FrameRangeAnimation* proj_fr_animation;

	Sprite* proj = new Sprite(guma_x + 1, guma_y + 1, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Guma.projectile")), "Guma.projectile");
	//proj->SetMover(MakeSpriteGridLayerMover(&GameGrid,proj));
	proj->SetMover([proj](const SDL_Rect& rect, int* dx, int* dy) { proj->SetPos(rect.x + *dx, 0); });
	proj->GetGravityHandler().gravityAddicted = false;
	proj->SetHasDirectMotion(true);
	//sprite_manager.Add(proj);
	proj_fr_animator = new FrameRangeAnimator();
	//more reps = more range ,more plates = more dates
	proj_fr_animation = new FrameRangeAnimation("projectile.fr", 0, 3, 20, 0, 0, 100);
	proj_moving_animator = new MovingAnimator();
	proj_moving_animation = new MovingAnimation("projectile.mv", 30, -3, 0, 50);
	proj_moving_animator->SetOnAction([proj](Animator* animator, const Animation& anim) { Sprite_MoveAction(proj, animator, (MovingAnimation&)anim); });
	

	proj_fr_animator->SetOnAction([proj](Animator* animator, const Animation& anim) { FrameRange_Action(proj, animator, (FrameRangeAnimation&)anim); });
	proj_fr_animator->SetOnFinish([](Animator* animator) {});
	proj_fr_animator->SetOnStart([](Animator* animator) {});
	

	
	proj_moving_animator->SetOnFinish([proj, character](Animator* animator) {CollisionHandler.Cancel(proj, &link_cl.get_current());	sprite_manager.Remove(proj); proj->SetPos(character->get_current().GetBox().x , character->get_current().GetBox().y ); });
	proj_moving_animator->SetOnStart([proj, character](Animator* animator) {CollisionHandler.Register(&link_cl.get_current(), proj, [](Sprite* s1, Sprite* s2) {
		std::cout << "hit by proj"; });	proj->SetPos(character->get_current().GetBox().x, character->get_current().GetBox().y);  sprite_manager.Add(proj); });
	
	
	character->set_fire([proj_fr_animation, proj_fr_animator, proj_moving_animation, proj_moving_animator, proj]() {

		proj_fr_animator->Start(proj_fr_animation, GetSystemTime());
	    proj_moving_animator->Start(proj_moving_animation, GetSystemTime());

		});
}

void initialise_guma(GridLayer GameGrid) {
	GameCharacter* guma = character_manager.create(Character_t::Guma_t);
	initialise_guma_films(guma);
	Sprite* g_sprite = initialise_guma_sprites(guma, GameGrid);
	initialise_guma_animations(g_sprite, guma);
	init_projectile(g_sprite, guma);
	sprite_manager.Add(g_sprite);

	CollisionHandler.Register(&link_cl.get_current(), g_sprite, [guma](Sprite* s1, Sprite* s2) {
		if (s1->GetCombatSystem().getAttackingMode()) {
			int damageDealt = s1->GetCombatSystem().getDamage();
			s2->GetCombatSystem().ReceivedDamage(damageDealt);
			if (s2->GetCombatSystem().getHp() <= 0 && guma->get_id() != "Guma.dead") {
				FrameRangeAnimator* guma_animator = new FrameRangeAnimator();
				FrameRangeAnimation* guma_animation = new FrameRangeAnimation("guma.fr", 0, 1, 1, 0, 0, 2000);
				guma->set_film("Guma.death", const_cast<AnimationFilm*>(FilmHolder.GetFilm("Guma.death")));
				guma->set_animation("Guma.death.animation", guma_animation);
				guma->set_animator("Guma.death.animator", guma_animator);
				guma->set_id("Guma.dead");
				guma->stop_animators();
				s2->change_film(const_cast<AnimationFilm*>(FilmHolder.GetFilm("Guma.death")));
				s2->set_state("dead");
				guma_animator->Start(guma_animation, GetSystemTime());
				s2->set_alive(false);
			}

			std::cout << s2->GetCombatSystem().getHp() << std::endl;
		}
		std::cout << s2->GetCombatSystem().getHp() << std::endl;
		});

	character_manager.add_to_current(guma);
}