#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "SDL.h"

using conf_map = std::map<std::string, std::any>;

std::vector<std::string> get_sprite_film_list(const std::string& sprite_name);


std::string get_sprite_initial_film(const std::string& sprite_name);

SDL_Point get_sprite_start_pos(const std::string& sprite_name);
SDL_Point get_sprite_start_pos_scaled(const std::string& sprite_name);


std::vector<std::string> get_sprite_name_list();

std::vector<std::string> get_elevator_names();

size_t get_sprite_num(const std::string& id);

std::vector<SDL_Point> get_pos_list(const std::string& id, const int scale);

std::string get_sprite_type(const std::string& id);