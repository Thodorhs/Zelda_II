#include "Initialise_characters.h"

#include "../../../Engine/Include/Util/EngineDefines.h"

Link_Class Link_Class::singleton;//this as well ffff u aa
//create with factory
//init films animations
//init animators
//add to sprite manager
CharacterManager CharacterManager::singleton;
CollisionChecker CollisionChecker::singleton;

struct cor {
	int x, y;
}typedef cords;
cords ElevatorCordPairs[NUMBEROFELEVATORS][2] = { {{36*32,13*32},{153*32 - 250,12*32}} , {{36,13 },{153 ,12}} ,{{36 ,13},{153,12}} ,{{36,13},{153,12}} };


void initialise_films_link(GridLayer GameGrid) {
	AnimationFilm* run_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.left"));
	AnimationFilm* attack_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.left"));
	AnimationFilm* attack_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Attack.right"));
	AnimationFilm* fall_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.falling.left"));
	AnimationFilm* fall_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.falling.right"));
	AnimationFilm* jump_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.jump.left"));
	AnimationFilm* jump_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.jump.right"));
	AnimationFilm* crouch_right = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Crouch.right"));
	AnimationFilm* crouch_left = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Crouch.right"));
	link_cl.set_film("Link.Run.left", run_left);
	link_cl.set_film("Link.Attack.left", attack_left);
	link_cl.set_film("Link.Attack.right", attack_right);
	link_cl.set_film("Link.falling.left", fall_left);
	link_cl.set_film("Link.falling.right", fall_right);
	link_cl.set_film("Link.jump.left", jump_left);
	link_cl.set_film("Link.jump.right", jump_right);
	link_cl.set_film("Link.Crouch.left", crouch_left);
	link_cl.set_film("Link.Crouch.right", crouch_right);
}

void initialise_doors_films() {
	//Sprite* door = new Sprite(195 * 32, 10 * 32, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Door")), "Door");
}

void initialise_items_films() {
	Sprite* Key = new Sprite(132, 32, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Key")), "Key1");
	sprite_manager.Add(Key);
}

Sprite* Initialise_sprites_link(GridLayer GameGrid) {
	Sprite *Link = new Sprite(200, 200, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Link.Run.right")), "Link");
	Link->SetCombatSystem(100, 6);
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
	Animation* attack_anim = new FrameRangeAnimation("link.attack", 0, 1, 1, 0, 0, 100);

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
void initialise_elevator(TileLayer& Actionlayer,TileLayer& HorizonLayer) {
    Sprite* Elevator_1 = new Sprite(36 * 32, 13 * 32, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Elevator")), "Elevator_1");
	sprite_manager.Add(Elevator_1);
	Sprite* Elevator_2 = new Sprite(153 * 32, 12 * 32, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Elevator")), "Elevator_2");
	sprite_manager.Add(Elevator_2);

	std::vector<Sprite*>elevators;
	elevators.push_back(Elevator_1);
	elevators.push_back(Elevator_2);
	SDL_Rect r;
	
	int index = 0;
	for(auto it : elevators){
		CollisionHandler.Register(&link_cl.get_current(), it,
			[index,&r,&Actionlayer,&HorizonLayer](Sprite* s1, Sprite* s2) {
				int temp = index % 2;
				if (temp==1) {
					if (link_cl.GetisLinkPressingDown()) {
						std::cout << "ChangeROOM1: " << ElevatorCordPairs[index][0].x<< ElevatorCordPairs[index][0].y << std::endl;
						link_cl.get_current().SetPos(ElevatorCordPairs[index][0].x + 64, ElevatorCordPairs[index][0].y - 32);
						r.x = ElevatorCordPairs[index][0].x-250;
						r.y = 0;
						r.w = Actionlayer.GetViewWindow().w;
						r.h = Actionlayer.GetViewWindow().h;
						Actionlayer.SetViewWindow(r);
						HorizonLayer.SetViewWindow(r);
						Actionlayer.NextRoom();
						HorizonLayer.NextRoom();
					}
				} else {
					if (link_cl.GetisLinkPressingDown()) {
						std::cout << "ChangeROOM2: " << ElevatorCordPairs[index][1].x <<", " << ElevatorCordPairs[index][1].y << std::endl;
						link_cl.get_current().SetPos(ElevatorCordPairs[index][1].x + 320, ElevatorCordPairs[index][1].y - 32);
						r.x = ElevatorCordPairs[index][1].x;
						r.y = 0;
						r.w = Actionlayer.GetViewWindow().w;
						r.h = Actionlayer.GetViewWindow().h;
						Actionlayer.SetViewWindow(r);
						HorizonLayer.SetViewWindow(r);
						Actionlayer.NextRoom();
						HorizonLayer.NextRoom();
					}
				}
			
			link_cl.SetisLinkPressingDown(false);
			});
		index++;
	}

	

}


void initialise_link(GridLayer GameGrid) {
	Sprite* link = Initialise_sprites_link(GameGrid);
	initialise_films_link(GameGrid);
	initialize_animators_link(link);
	
}


void initialise_enemies(GridLayer GameGrid) {
	initialise_palace_bot(GameGrid);
	initialise_guma(GameGrid);
	initialise_wosu(GameGrid, wosu_x_1, wosu_y_1,"1");
	initialise_wosu(GameGrid, wosu_x_2, wosu_y_2,"2");
	initialise_wosu(GameGrid, wosu_x_3, wosu_y_3,"3");
	initialise_wosu(GameGrid, wosu_x_4, wosu_y_4,"4");
	initialise_items_films();
	for (auto it : character_manager.get_current_characters()) {
		it->print_character();
	}

}