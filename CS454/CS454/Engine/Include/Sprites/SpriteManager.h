#include "Sprite.h"
#include <list>

class SpriteManager final {
public:
	using SpriteList = std::list<Sprite*>;
	using TypeLists = std::map<std::string, SpriteList>;
private:
	SpriteList dpyList;
	TypeLists types;
	static SpriteManager singleton;
public:
	void Add(Sprite* s) { dpyList.push_back(s); } // insert by ascending zorder
	void Remove(Sprite* s) {
		for (auto it : dpyList) {
			if (it->GetTypeId() == s->GetTypeId()) {
				dpyList.remove(it);
				return;
			}
		}
	}
	void AddforDisplay(Sprite *s)
	{
		assert(s);
		if (Get_sprite_by_id(s->GetTypeId()))
			return;
		Add(s);
	}

	void AddforDisplay(const std::string & type,const std::string& id)
	{
		for(auto &it : GetTypeList(type))
		{
			if (it->GetTypeId() == id) {
				Add(it);
				break;
			}
		}
	}


	void AddtoMap(const std::string& type,Sprite* s)
	{
		types[type].push_back(s);
	}

	auto GetDisplayList(void) -> const SpriteList&
	{
		return dpyList;
	}
	auto GetTypeList(const std::string& typeId) -> const SpriteList&
	{
		return types[typeId];
	}
	static auto GetSingleton(void) -> SpriteManager&
	{
		return singleton;
	}
	static auto GetSingletonConst(void) -> const SpriteManager&
	{
		return singleton;
	}

	auto Get_sprite_by_id(const std::string& id) -> Sprite*
	{
		for(auto &it : dpyList)
		{
			if (it->GetTypeId() == id)
				return it;
		}
		return nullptr;
	}
};
