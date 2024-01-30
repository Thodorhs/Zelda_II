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
	Char_list dead_chars;

	CharacterManager(void) = default;
	CharacterManager(const CharacterManager&) = delete;
	CharacterManager(CharacterManager&&) = delete;
	static CharacterManager singleton;

public:
	void Register_to_Dead(Character *c)
	{
		dead_chars.push_back(c);
	}

	Char_list Get_dead() { return dead_chars; }

	void Register(Character* character,const std::string &id) {
		assert(character);
		Character_map[id].push_back(character);
	}

	auto GetTypeList(const std::string& typeId) -> const Char_list&
	{
		return Character_map[typeId];
	}

	auto GetTypeListNoConst(const std::string& typeId) ->  Char_list&
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

	int delete_index(const std::string& type,const std::string &id)
	{
		auto list = GetTypeList(type);
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->get_id() == id)
				return i;
			
		}
	}
	

	void Erase(const std::string &id,const std::string& type)
	{
		auto del = GetTypeListNoConst(type).erase(GetTypeListNoConst(type).begin() + delete_index(type, id));
		//free(*del);
		//Register_to_Dead(*del);
	}


	bool isAlive(const std::string& id,const std::string &type) {
		
		auto c = Get_by_Id(id,type);
		if (c && c->is_Alive())
			return true;
		return false;
	}

	static auto GetSingleton(void) -> CharacterManager& { return singleton; }


};