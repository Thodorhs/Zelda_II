#pragma once
#include "../../Include/Link/Link.h"
#include "../../Include/StatPrinting/StatPrinting.h"
#include "../../../../Engine/Include/TileLayer.h"
#include "SDL_ttf.h"
#include <filesystem>
#include <string>
#include "../../../../Engine/Include/Util/Print.h"
TTF_Font* font;
int milestone = 100;
auto font_path() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "ThirdParty/zelda-ii-the-adventure-of-link.ttf";
	return full_asset_path;
}
auto health_path() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests/UnitTest3/UnitTest3Media/health.png";
	return full_asset_path;
}
bool init_ttf() {
	bool b = TTF_Init() < 0;
	if (!b) {
		font = TTF_OpenFont(font_path().c_str(), FONT_SIZE);
		if (font == NULL) {
			pr_info("error opening Font.");
			return true;
		}
	}
	return b;
}
SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_Color col = { r,g,b,a };
	return col;
}

void RenderHPBar(int x, int y, int w, int h, int life, SDL_Color FGColor, SDL_Renderer* renderer) {
	SDL_Color old;
	SDL_Rect r = { x,y,w+1,h };
	SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
	SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	SDL_Rect fgrect = { x+1, y+2, w-1.3*(100-life), h-3 };
	SDL_RenderFillRect(renderer, &fgrect);
	SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
	SDL_Surface* healthbar_sur = IMG_Load(health_path().c_str());
	SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(renderer, healthbar_sur);
	SDL_RenderCopy(renderer, healthbar_tex, NULL, &r);
	SDL_FreeSurface(healthbar_sur);
	SDL_DestroyTexture(healthbar_tex);
}
void RenderMagicBar(int x, int y, int w, int h, int magic, SDL_Color FGColor, SDL_Renderer* renderer) {
	SDL_Color old;
	SDL_Rect r = { x,y,w + 1,h };
	SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
	SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	SDL_Rect fgrect = { x + 1, y + 2, w - 1.3 * (200 - magic), h - 3 };
	SDL_RenderFillRect(renderer, &fgrect);
	SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
	SDL_Surface* healthbar_sur = IMG_Load(health_path().c_str());
	SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(renderer, healthbar_sur);
	SDL_RenderCopy(renderer, healthbar_tex, NULL, &r);
	SDL_FreeSurface(healthbar_sur);
	SDL_DestroyTexture(healthbar_tex);
}

void render_str(SDL_Renderer* renderer, TileLayer* layer, std::string txt, SDL_Point p) {
	//pr_info(all.c_str());
	SDL_Surface* fontxt = TTF_RenderText_Solid(font, txt.c_str(), { 255, 255, 255 });
	int texW = 0;
	int texH = 0;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, fontxt);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dst = { p.x, p.y, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_FreeSurface(fontxt);
	SDL_DestroyTexture(texture);
	return;
}

void render_stats(SDL_Renderer* renderer, TileLayer* layer) {
	Link& link = Link::GetSingleton();
	std::string str = std::to_string(link.getLifes()).c_str();
	str = "LIFE - " + str;
	render_str(renderer, layer, str, { 255,0 });

	str = "MAGIC";
	render_str(renderer, layer, str, { 50,0 });

	str = "NEXT";
	render_str(renderer, layer, str, { 505,0 });
	str = std::to_string(link.getPoints()).c_str();
	if (milestone - link.getPoints() < 0) {
		milestone = milestone + 100;
	}
	str = str+"/"+std::to_string(milestone).c_str();
	render_str(renderer, layer, str, { 490,20 });

	int life = link.getHealth();
	if (life >= 0) {
		SDL_Color c = color(181, 49, 32, 255);
		RenderHPBar(257, 30, 130, 18, life, c, renderer);
	}

	int magic = link.getMagic();
	if (magic >= 0) {
		SDL_Color c = color(74, 34, 223, 255);
		RenderMagicBar(30, 30, 130, 18, magic, c, renderer);
	}
	
}