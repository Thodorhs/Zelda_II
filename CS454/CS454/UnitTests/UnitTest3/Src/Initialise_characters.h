#pragma once
#include "Link_test/Link.h"
#include "../Src/Link_test/GameCharacters.h"
#include "../../../Engine/Include/Sprites/CollisionChecker.h"
#define bot_x 200
#define bot_y 300

#define guma_x 183*32
#define guma_y 10*32
#define wosu_x_1 128*32
#define wosu_y_1 10*32
#define wosu_x_2 150*32
#define wosu_y_2 10*32
#define wosu_x_3 165*32
#define wosu_y_3 10*32
#define wosu_x_4 173*32
#define wosu_y_4 10*32

static CharacterManager& character_manager = CharacterManager::GetSingleton();
static CollisionChecker& CollisionHandler = CollisionChecker::GetSingleton();
static Link_Class& link_cl = Link_Class::GetSingleton();
static AnimationFilmHolder& FilmHolder = AnimationFilmHolder::getInstance();
static AnimatorManager& AnimManager = AnimatorManager::GetSingleton(); // Take the singleton
static SystemClock& my_system_clock = SystemClock::Get();
static SpriteManager& sprite_manager = SpriteManager::GetSingleton();
static DestructionManager& destruction_man = DestructionManager::Get();
void initialise_guma(GridLayer GameGrid);
void initialise_palace_bot(GridLayer GameGrid);
void initialise_enemies(GridLayer GameGrid);
void initialise_link(GridLayer GameGrid);
void initialise_elevator(TileLayer &Actionlayer,TileLayer &HorizonLayer);
void initialise_wosu(GridLayer GameGrid, int x, int y, std::string wosu_no);