#pragma once
#include "Character.h"
#include <vector>
#include <assert.h>
#include <map>

class CharacterManager {
	using Char_list = std::vector<Character*>;
	using Type_List = std::map<std::string, Char_list>;
private:
	
	Type_List Character_map;

	CharacterManager(void) = default;
	CharacterManager(const CharacterManager&) = delete;
	CharacterManager(CharacterManager&&) = delete;
	static CharacterManager singleton;

public:
	

	void Register(Character* character,const std::string &id) {
		assert(character);
		Character_map[id].push_back(character);
	}

	auto GetTypeList(const std::string& typeId) -> const Char_list&
	{
		return Character_map[typeId];
	}

	Character* Get_by_Id(const std::string &id,const std::string &type) {
		auto list = GetTypeList(type);

		for (auto& it : list) {
			if (it->get_id() == id)
				return it;
		}
		return nullptr;
	}

	bool isAlive(const std::string& id,const std::string &type) {
		
		auto c = Get_by_Id(id,type);
		if (c && c->is_Alive())
			return true;
		return false;
	}

	static auto GetSingleton(void) -> CharacterManager& { return singleton; }


};