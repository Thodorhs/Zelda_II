#include "Initialise_characters.h"


Sprite* initialise_wosu_sprites(GameCharacter* character, GridLayer GameGrid,int x,int y,std::string no) {
    Sprite* wosu = new Sprite(x, y, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Wosu")), "Wosu"+no);
    wosu->SetMover(MakeSpriteGridLayerMover(&GameGrid, wosu));
    wosu->SetCombatSystem(80, 1);
    PrepareSpriteGravityHandler(&GameGrid, wosu);


    wosu->GetGravityHandler().gravityAddicted = true;
    wosu->GetGravityHandler().SetOnStartFalling(
        [character]() {character->stop_animators();
    return; });
    wosu->GetGravityHandler().SetOnStopFalling(
        []() {
            //Link->GetGravityHandler().isFalling = false;
            //std::cout << "called";
            //Link->SetHasDirectMotion(false);
        });
    wosu->Move(1, 0);
    character->set_current(wosu);
    return wosu;
   
}

void initialise_wosu_animations(GameCharacter* character,Sprite *wosu) {
    MovingAnimator* move = new MovingAnimator();
    MovingAnimation* move_anim = new MovingAnimation("wosu.move", 1, 0, 0, 100);
    character->set_animation("wosu.move", move_anim);
    character->set_animator("move", move);
    FrameRangeAnimator* fr_wosu = new FrameRangeAnimator();
    FrameRangeAnimation* fr_anim = new FrameRangeAnimation("wosu.fr", 0, 1, 10, 0, 0, 100);

    fr_wosu->SetOnAction([wosu](Animator* animator, const Animation& anim) {
        FrameRange_Action(wosu, animator, (const FrameRangeAnimation&)anim);
        });
    fr_wosu->SetOnStart([](Animator* animator) {});
    fr_wosu->SetOnFinish([](Animator* animator) {});
    character->set_animation("wosu.fr.anim", fr_anim);
    character->set_animator("wosu.fr", fr_wosu);
}

void initialise_wosu(GridLayer GameGrid,int x,int y,std::string wosu_no) {
    GameCharacter* wosu = character_manager.create(Character_t::Wosu_t);
    Sprite *wosu_s = initialise_wosu_sprites(wosu, GameGrid,x,y,wosu_no);
    initialise_wosu_animations(wosu,wosu_s);
    sprite_manager.Add(wosu_s);

    CollisionHandler.Register(&link_cl.get_current(), wosu_s, [wosu](Sprite* s1, Sprite* s2) {
       if (s1->GetCombatSystem().getAttackingMode()) {
           int damageDealt = s1->GetCombatSystem().getDamage();
           s2->GetCombatSystem().ReceivedDamage(damageDealt);
           if (s2->GetCombatSystem().getHp() <= 0 && wosu->get_id() != "Wosu.dead") {
               FrameRangeAnimator* wosu_animator = new FrameRangeAnimator();
               FrameRangeAnimation* wosu_animation = new FrameRangeAnimation("wosu.fr", 0, 1, 1, 0, 0, 2000);
               wosu->set_film("Wosu.death", const_cast<AnimationFilm*>(FilmHolder.GetFilm("Wosu.death")));
               wosu->set_animation("Wosu.death.animation", wosu_animation);
               wosu->set_animator("Wosu.death.animator", wosu_animator);
               wosu->set_id("Wosu.dead");
               s2->change_film(const_cast<AnimationFilm*>(FilmHolder.GetFilm("Wosu.death")));
               s2->set_state("dead");
			   wosu_animator->Start(wosu_animation, GetSystemTime());
               s2->set_alive(false);
           }

           std::cout << s2->GetCombatSystem().getHp() << std::endl;
       }
        });
    character_manager.add_to_current(wosu);

}