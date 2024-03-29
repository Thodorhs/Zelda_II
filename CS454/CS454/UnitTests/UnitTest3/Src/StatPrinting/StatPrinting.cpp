#pragma once
#include "../../Include/Link/Link.h"
#include "../../Include/StatPrinting/StatPrinting.h"
#include "../../../../Engine/Include/TileLayer.h"
#include "SDL_ttf.h"
#include <filesystem>
#include <string>
#include "../../../../Engine/Include/Util/Print.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../../../Engine/Include/Sprites/SpriteManager.h"
#include "../../../../Engine/Include/GameLoopFuncs/Input.h"
TTF_Font* font;
TTF_Font* bgfont;
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
		bgfont = TTF_OpenFont(font_path().c_str(), FONT_SIZE);
		TTF_SetFontOutline(bgfont, 0);
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
void RenderHPBoss(int x, int y, int w, int h, int life, SDL_Color FGColor, SDL_Renderer* renderer) {
    SDL_Color old;
    SDL_Rect r = { x,y,w + 1,h };
    SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
    SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    SDL_Rect fgrect = { x + 1, y + 2, w - 3 * (600 - life)/6, h - 3 };
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
	SDL_Rect fgrect = { x + 1, y + 2, w - 1.3 * (200 - magic)/2, h - 3 };
	SDL_RenderFillRect(renderer, &fgrect);
	SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
	SDL_Surface* healthbar_sur = IMG_Load(health_path().c_str());
	SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(renderer, healthbar_sur);
	SDL_RenderCopy(renderer, healthbar_tex, NULL, &r);
	SDL_FreeSurface(healthbar_sur);
	SDL_DestroyTexture(healthbar_tex);
}

void render_str(SDL_Renderer* renderer, TileLayer* layer, std::string txt, SDL_Point p) {
	SDL_Surface* fontxt = TTF_RenderText_Blended_Wrapped(font, txt.c_str(), { 255, 255, 255 },0);
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
void render_str_c(SDL_Renderer* renderer, TileLayer* layer, std::string txt, SDL_Point p,SDL_Color c) {
	SDL_Surface* fontxt = TTF_RenderText_Blended_Wrapped(font, txt.c_str(), c, 0);
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
void render_end(SDL_Renderer* renderer, TileLayer* layer, std::string txt, SDL_Point p) {
	SDL_Surface* fontxt = TTF_RenderText_Blended_Wrapped(font, txt.c_str(), { 255,255,255,255 }, 0);
	SDL_Surface* fonbg = TTF_RenderText_Blended_Wrapped(bgfont, txt.c_str(), { 65,18,207,255 }, 0);
	/*forground*/
	int texW = 0;
	int texH = 0;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, fontxt);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dst = { p.x, p.y, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	/*backround*/
	texW = 0;
	texH = 0;
	texture = SDL_CreateTextureFromSurface(renderer, fonbg);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dst = { p.x, p.y, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dst);

	SDL_FreeSurface(fontxt);
	SDL_FreeSurface(fonbg);
	SDL_DestroyTexture(texture);
	return;
}

void render_stats(SDL_Renderer* renderer, TileLayer* layer) {
	Link& link = Link::GetSingleton();
	std::string str;
	auto maz = CharacterManager::GetSingleton().Get_by_Id("Mazura","Mazura");
	if(link.isAlive()){
		str = std::to_string(link.getLifes()).c_str();
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
		if(Link::GetSingleton().inBoss()){
			if (maz->is_Alive()) {
				int hp = maz->get_health();
				if(hp>=0){
					SDL_Color c = color(181, 49, 32, 255);
					RenderHPBoss(160, 440, 300, 16, hp, c, renderer);
					auto [x,y,w,h] = SpriteManager::GetSingleton().Get_sprite_by_id("Mazura")->GetBox();
					auto [vx, vy, vw, vh] = layer->GetViewWindow();
					auto scale = layer->get_scale();
					str = "Giga Horseman";
					render_str(renderer, layer, str, { x - 83 - vx*scale, y - 30 - vy*scale });
				}
			}
		}
		if (Link::GetSingleton().getstart() && !InputKeys::GetSingleton().isPaused()) {
			str = "Esc - Info";
			render_str(renderer, layer, str, { 230,180 });
		}
		if (Link::GetSingleton().getfinished()) {
			str = "Level 1 Completed!!!";
			render_str(renderer, layer, str, { 185,180 });
			
		}
		if (Link::GetSingleton().getcred()) {
			str = "THEODOROS PONTZOUKTZIDIS csd4336\nDIMITRIOS VLACHOS csd4492\nUniversity of Crete\nDepartment of Computer Science\nCS - 454. Development of Intelligent Interfaces and Games\nTerm Project, Fall Semester 2023";
			render_str(renderer, layer, str, { 20,220 });
		}
		if (InputKeys::GetSingleton().isPaused()) {
			str = "Paused.";
			render_str_c(renderer, layer, str, { 265,60 },{ 255, 255, 255, 255 });
			str = "INPUT.\nA,D - Move       B - Attack\nW - Crouch       S - crouch\n\nSPELLS.\nH - Heal       1 - Shield\n\nGAME INFO.\nG - HitBoxes-Grid       F1 - Cheat\nF - Info";
			render_str_c(renderer, layer, str, { 20,135 },{ 255, 0, 0, 255 });
		}
    }else{
        str = "Game Over";
        render_str(renderer, layer, str, { 240,180 });
	}
	
}