#include "../../Include/Characters/CharacterManager.h"
#include "../../../Engine/Include/Sprites/SpriteManager.h"
CharacterManager CharacterManager::singleton;

using SList = std::list<Sprite*>;

void register_gumas(SList gumas) {

}

void register_bots(SList bots) {
	for (auto& it : bots) {
		Character *c = new Character(it->GetTypeId(), "bot");
		CharacterManager::GetSingleton().Register(c, c->get_type());
	}
}

void register_Link(Sprite *s) {
	
}


void init_characters() {
	auto gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	auto link  = SpriteManager::GetSingleton().GetTypeList("Link").begin();
	auto bots = SpriteManager::GetSingleton().GetTypeList("Palace_bot");
	
	register_Link(*link);
	register_bots(bots);
	register_gumas(gumas);
}