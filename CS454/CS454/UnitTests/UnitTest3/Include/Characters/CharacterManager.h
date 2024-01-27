#pragma once
#include "Character.h"
#include <vector>
#include <assert.h>
#include <map>

class CharacterManager {
	using Char_list = std::vector<Character*>;
	using Type_List = std::map<std::string, Char_list>;
private:
	Char_list Characters;
	Type_List Character_map;

	CharacterManager(void) = default;
	CharacterManager(const CharacterManager&) = delete;
	CharacterManager(CharacterManager&&) = delete;
	static CharacterManager singleton;

public:
	void Register(Character* character) {
		assert(character);
		Characters.push_back(character);
	}

	void Register(Character* character,const std::string &id) {
		assert(character);
		Character_map[id].push_back(character);
	}

	auto GetTypeList(const std::string& typeId) -> const Char_list&
	{
		return Character_map[typeId];
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
		if (c && c->is_Alive())
			return true;
		return false;
	}

	static auto GetSingleton(void) -> CharacterManager& { return singleton; }


};