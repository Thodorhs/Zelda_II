#include "Initialise_characters.h"

void initialise_palacebot_films(GameCharacter* enemy) {
    AnimationFilm* enemy_film = const_cast<AnimationFilm*>(FilmHolder.GetFilm("Palace.bot.default"));
    enemy->set_film("id", enemy_film);

}

Sprite* initialise_palacebot_sprites(GameCharacter* character, GridLayer GameGrid) {
    Sprite* palace_bot = new Sprite(bot_x, bot_y, const_cast<AnimationFilm*>(FilmHolder.GetFilm("Palace.bot")), "Palace.bot");
    palace_bot->SetMover(MakeSpriteGridLayerMover(&GameGrid, palace_bot));
    palace_bot->SetCombatSystem(160, 4);
    PrepareSpriteGravityHandler(&GameGrid, palace_bot);


    palace_bot->GetGravityHandler().gravityAddicted = true;
    palace_bot->GetGravityHandler().SetOnStartFalling(
        [character]() {character->stop_animators();
    return; });
    palace_bot->GetGravityHandler().SetOnStopFalling(
        []() {
            //Link->GetGravityHandler().isFalling = false;
            //std::cout << "called";
            //Link->SetHasDirectMotion(false);
        });
    palace_bot->Move(1, 0);
    sprite_manager.Add(palace_bot);
    character->set_current(palace_bot);
    return palace_bot;
}

void initialise_palacebot_animations(GameCharacter* character) {
    Animator* move = new MovingAnimator();
    Animation* move_anim = new MovingAnimation("bot.move", 1, 0, 0, 100);
    character->set_animation("bot.move", move_anim);
    character->set_animator("move", move);

}

void initialise_palace_bot(GridLayer GameGrid) {
    GameCharacter* bot = character_manager.create(Character_t::GreatPalaceBot_t);
    Sprite* bot_s = initialise_palacebot_sprites(bot, GameGrid);
    initialise_palacebot_films(bot);

    initialise_palacebot_animations(bot);

    CollisionHandler.Register(&link_cl.get_current(), bot_s, [](Sprite* s1, Sprite* s2) {
        if (s1->GetCombatSystem().getAttackingMode()) {
            int damageDealt = s1->GetCombatSystem().getDamage();
            s2->GetCombatSystem().ReceivedDamage(damageDealt);
            std::cout << s2->GetCombatSystem().getHp() << std::endl;
        }
        });
    character_manager.add_to_current(bot);

}