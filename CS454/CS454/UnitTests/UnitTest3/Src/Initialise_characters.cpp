#include "Initialise_characters.h"

CharacterManager CharacterManager::singleton;
Link_Class Link_Class::singleton;//this as well ffff u aa
//create with factory
//init films animations
//init animators
//add to sprite manager



void initialise_films_link(GridLayer GameGrid) {
	AnimationFilm* run_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.left"));
	AnimationFilm* attack_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.left"));
	AnimationFilm* attack_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.right"));
	AnimationFilm* fall_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.falling.left"));
	AnimationFilm* fall_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.falling.right"));
	AnimationFilm* jump_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.jump.left"));
	AnimationFilm* jump_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.jump.right"));
	link_cl.set_film("Link.Run.left", run_left);
	link_cl.set_film("Link.Attack.left", attack_left);
	link_cl.set_film("Link.Attack.right", attack_right);
	link_cl.set_film("Link.falling.left", fall_left);
	link_cl.set_film("Link.falling.right", fall_right);
	link_cl.set_film("Link.jump.left", jump_left);
	link_cl.set_film("Link.jump.right", jump_right);
}

Sprite* Initialise_sprites_link(GridLayer GameGrid) {
	Sprite *Link = new Sprite(200, 200, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.right")), "Link");
	link_cl.set_film("Link.Run.right", const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.right")));

	Link->SetMover(MakeSpriteGridLayerMover(&GameGrid, Link));
	PrepareSpriteGravityHandler(&GameGrid, Link);


	Link->GetGravityHandler().gravityAddicted = true;
	Link->GetGravityHandler().SetOnStartFalling(
		[]() {link_cl.stop_animators();
	return; });
	Link->GetGravityHandler().SetOnStopFalling(
		[]() {
			//Link->GetGravityHandler().isFalling = false;
			//std::cout << "called";
			//Link->SetHasDirectMotion(false);
		});

	sprite_manager.Add(Link);
	return Link;
}






void initialize_animators_link(Sprite* Link) {
	Animator* move = new MovingAnimator();
	Animation* move_anim = new MovingAnimation("link.move", 1, 0, 0, 100);

	Animator* fr = new FrameRangeAnimator();
	Animation* run_anim = new FrameRangeAnimation("link.run", 0, 3, 1, 0, 0, 0);

	Animator* attack = new FrameRangeAnimator();
	Animation* attack_anim = new FrameRangeAnimation("link.attack", 0, 3, 1, 0, 0, 100);

	Animator* jump = new MovingAnimator();
	Animation* jump_anim = new MovingAnimation("link.jump", 1, 0, 0, 40);

	//ATTACK

	attack->SetOnAction([Link](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	attack->SetOnStart([](Animator* animator) {});
	attack->SetOnFinish([](Animator* animator) {});


	//MOVE

	move->SetOnAction([Link](Animator* animator, const Animation& anim) {
		Sprite_MoveAction(Link, animator, (const MovingAnimation&)anim);
		});
	move->SetOnStart([](Animator* animator) {});
	move->SetOnFinish([](Animator* animator) {});


	fr->SetOnAction([Link](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	fr->SetOnStart([](Animator* animator) {});
	fr->SetOnFinish([](Animator* animator) {});


	jump->SetOnAction([Link](Animator* animator, const Animation& anim) {
		FrameRange_Action(Link, animator, (const FrameRangeAnimation&)anim);
		});
	jump->SetOnStart([](Animator* animator) {});
	jump->SetOnFinish([](Animator* animator) {});

	link_cl.set_animation("link.move", move_anim);
	link_cl.set_animation("link.run", run_anim);

	link_cl.set_animator("move", move);
	link_cl.set_animator("fr", fr);

	link_cl.set_animation("link.attack", attack_anim);
	link_cl.set_animator("attack", attack);

	link_cl.set_animation("link.jump", jump_anim);
	link_cl.set_animator("jump", jump);

	link_cl.set_current(Link);

}
Sprite* initialise_elevator() {
    Sprite* Elevator = new Sprite(36 * 32, 13 * 32, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Elevator")), "Elevator");
	sprite_manager.Add(Elevator);
	return Elevator;
}


void initialise_link(GridLayer GameGrid) {
	Sprite* link = Initialise_sprites_link(GameGrid);
	initialise_films_link(GameGrid);
	initialize_animators_link(link);
	
}


void initialise_enemies(GridLayer GameGrid) {
	initialise_palace_bot(GameGrid);
	initialise_guma(GameGrid);
	for (auto it : character_manager.get_current_characters()) {
		it->print_character();
	}

}