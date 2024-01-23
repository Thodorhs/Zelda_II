
#include "Character.h"
#include <vector>
#include <assert.h>
class CharacterManager {
private:
	std::vector<Character*> Characters;
	CharacterManager(void) = default;
	CharacterManager(const CharacterManager&) = delete;
	CharacterManager(CharacterManager&&) = delete;
	static CharacterManager singleton;

public:
	void Register(Character* character) {
		assert(character);
		Characters.push_back(character);
	}

	Character* Get_by_Id(const std::string &id) {
		for (auto& it : Characters) {
			if (it->get_id() == id)
				return it;
		}
		return nullptr;
	}

	bool isAlive(const std::string& id) {
		auto c = Get_by_Id(id);
		if (c && c->get_health() > 0)
			return true;
		return false;
	}

	static auto GetSingleton(void) -> CharacterManager& { return singleton; }


};