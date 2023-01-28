#pragma once
#include "Link_test/Link.h"
#include "../Src/Link_test/GameCharacters.h"
#include "../../../Engine/Include/Sprites/CollisionChecker.h"
#define bot_x 200
#define bot_y 300

#define guma_x 430
#define guma_y 300



static CharacterManager& character_manager = CharacterManager::GetSingleton();
static CollisionChecker& CollisionHandler = CollisionChecker::GetSingleton();
static Link_Class& link_cl = Link_Class::GetSingleton();
static AnimationFilmHolder& FilmHolder = AnimationFilmHolder::getInstance();
static AnimatorManager& AnimManager = AnimatorManager::GetSingleton(); // Take the singleton
static SystemClock& my_system_clock = SystemClock::Get();
static SpriteManager& sprite_manager = SpriteManager::GetSingleton();

void initialise_guma(GridLayer GameGrid);
void initialise_palace_bot(GridLayer GameGrid);
void initialise_enemies(GridLayer GameGrid);
void initialise_link(GridLayer GameGrid);
void initialise_elevator(TileLayer &Actionlayer,TileLayer &HorizonLayer);
