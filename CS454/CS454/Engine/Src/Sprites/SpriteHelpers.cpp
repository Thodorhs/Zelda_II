#include "../../Include/Sprites/SpriteHelpers.h"
#include "../../Include/Util/ConfigFuncs.h"


std::vector<std::string> get_sprite_film_list(const std::string& sprite_name)
{
	std::vector<std::string> list;
	auto sprite = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list").at(sprite_name));

	auto films = std::any_cast<conf_map>(sprite.at("Films"));
	for (auto& f : films)
	{
		list.push_back(std::any_cast<std::string>(f.second));
	}
	return list;
}

std::string get_sprite_initial_film(const std::string& sprite_name)
{
	return get_sprite_film_list(sprite_name).at(0);
}

SDL_Point get_sprite_start_pos(const std::string& sprite_name)
{
	std::vector<std::string> list;
	auto sprite = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list").at(sprite_name));

	int x = std::any_cast<int>(sprite.at("start_x"));
	int y = std::any_cast<int>(sprite.at("start_y"));
	return { x,y };
}


std::vector<std::string> get_sprite_name_list()
{
	std::vector<std::string> list;
	auto sprites = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list"));
	for (const auto& key : sprites | std::views::keys)
	{
		list.push_back(key);
	}
	return list;
}