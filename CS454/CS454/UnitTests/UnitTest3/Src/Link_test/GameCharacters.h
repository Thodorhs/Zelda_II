#pragma once
#include <map>
#include "../../../../Engine/Include/Util/SystemClock.h"
#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../../Engine/Include/KeyFrameAnimation/FilmParser.h"
#include "../../../../Engine/Include/Sprites/SpriteManager.h"
#include "../../../../Engine/Include/Animators/FrameRangeAnimator.h"

//abstract class gia kathe xaraktira ->ektos tou link
typedef enum Character_type_t{ 
	GreatPalaceBot_t,
	Wosu_t,
	Guma_t,
	Stalfos_t
}Character_t;
class GameCharacter;
class GameCharacter {
	private:
		Character_t type;
		std::string id;
		
	public:
		
		virtual Animator* get_animator(std::string id) = 0;
		virtual Animation* get_animation(std::string id) = 0;
		virtual AnimationFilm* get_film(std::string id) = 0;
		virtual	void set_film(std::string id, AnimationFilm* anim) = 0;
		virtual	void stop_animators() = 0;
		virtual	void set_current(Sprite* s) = 0;
		virtual Sprite& get_current() = 0;
		virtual void set_animator(std::string id, Animator* anim) = 0;
		virtual void set_animation(std::string id, Animation* anim) = 0;
		virtual void set_type(Character_t type) = 0;
		virtual void set_id(std::string id) = 0;
		virtual Character_t get_type() = 0;
		virtual std::string get_id() = 0;
		virtual void set_fire(std::function<void(void)> f) { return; }
		virtual void fire_action() { return; }
	    virtual ~GameCharacter(){}
		virtual void print_character() = 0;
		static auto create(Character_t type)->GameCharacter*;
};




class CharacterManager {

public:
	static  CharacterManager singleton;
	static auto GetSingleton(void) -> CharacterManager& { return singleton; }
	static auto GetSingletonConst(void) -> const CharacterManager& { return singleton; }
	//edw less ti type thes kai sto ftiaxnei to apothikeuei sto curr	
	GameCharacter* create(Character_t t) {
		type = t;
		curr = GameCharacter::create(type);
		assert(curr);
		return curr;
	}
	void add_to_current(GameCharacter* character) { curr_game_characters.push_back(character); }
	std::vector<GameCharacter*> get_current_characters() { return  curr_game_characters; }
	void remove(GameCharacter* toremove,Sprite *s) {
		int index = 0;
		for (auto it : curr_game_characters) {
			if (it->get_current().GetTypeId() == toremove->get_current().GetTypeId()) {
				curr_game_characters.erase(curr_game_characters.begin() + index);
			}
			index++;
		}
	}
private:
	GameCharacter* curr;
	Character_t type;
	std::vector<GameCharacter*> curr_game_characters;
	

	


};