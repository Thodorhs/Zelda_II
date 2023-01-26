#pragma once
#include "../Src/Link_test/GameCharacters.h"
#define bot_x 200
#define bot_y 300

#include "Link_test/Link.h"




static Link_Class& link_cl = Link_Class::GetSingleton();
static AnimationFilmHolder& FilmHolder = AnimationFilmHolder::getInstance();
static AnimatorManager& AnimManager = AnimatorManager::GetSingleton(); // Take the singleton
static SystemClock& my_system_clock = SystemClock::Get();
static SpriteManager& sprite_manager = SpriteManager::GetSingleton();

void initialise_enemies(GridLayer GameGrid);
void initialise_link(GridLayer GameGrid);
