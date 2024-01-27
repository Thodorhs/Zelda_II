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

std::vector<std::string> get_elevator_names()
{
	auto list = get_sprite_name_list();
	std::vector<std::string> elevators;
	for(auto it : list)
	{
		if (it.find("Elevator") != std::string::npos) {
			elevators.push_back(it);
		}
	}
	return elevators;
}


SDL_Point get_sprite_start_pos_scaled(const std::string& sprite_name)
{
	std::vector<std::string> list;
	auto sprite = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list").at(sprite_name));

	int x = std::any_cast<int>(sprite.at("start_x"));
	int y = std::any_cast<int>(sprite.at("start_y"));

	auto ac_scale = (int)get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_action");
	x *= ac_scale;
	y *= ac_scale;

	return { x,y };
}

size_t get_sprite_num(const std::string& id)
{
	
	auto sprite = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list").at(id));
	if (!sprite.contains("pos"))
		return 1;
	auto pos = std::any_cast<conf_map>(sprite.at("pos"));
	return pos.size();

}

SDL_Point entry_to_point(const conf_map& entry,int scale)
{
	int x = std::any_cast<int>(entry.at("x"));
	int y = std::any_cast<int>(entry.at("y"));
	return { x*scale,y*scale};
}


std::vector<SDL_Point> get_pos_list(const std::string& id,const int scale)
{
	std::vector<SDL_Point> pos_list;
	if(get_sprite_num(id) == 1)
	{
		SDL_Point pos = get_sprite_start_pos(id);
		pos.x *= scale;
		pos.y *= scale;
		pos_list.push_back(pos);
		return pos_list;
	}
	
	auto sprite = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list").at(id));
	auto pos= std::any_cast<conf_map>(sprite.at("pos"));
	for (auto& f : pos)
	{
		pos_list.push_back(entry_to_point(std::any_cast<conf_map>(f.second),scale));
	}
	return pos_list;
}

std::string get_sprite_type(const std::string& id)
{
	std::vector<std::string> list;
	auto sprite = std::any_cast<conf_map>(get_config_value<conf_map>(configurators_t::SPRITE_CONFIG, "Sprite_list").at(id));
	if (!sprite.contains("type"))
		return "none";
	return std::any_cast<std::string>(sprite.at("type"));
}