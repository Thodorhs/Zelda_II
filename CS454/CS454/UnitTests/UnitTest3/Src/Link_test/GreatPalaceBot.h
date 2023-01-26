#pragma once
#include "GameCharacters.h"

class GreatPalaceBot : public GameCharacter {
private:
	std::map<std::string, Animator*> animators;
	std::map<std::string, Animation*>animations;
	std::map<std::string, AnimationFilm*> bot_films;
	
	Sprite* current;
public:

	void print_character() { std::cout << "GreatPalaceBot!" << "\n"; }

	void set_current(Sprite* s) { current = s; }
	Sprite& get_current() { return *current; }
	void set_animator(std::string id, Animator* anim) {
		animators.insert({ id,anim });
	}
	void set_animation(std::string id, Animation* anim) {
		animations.insert({ id,anim });
	}

	Animator* get_animator(std::string id) {
		auto it = animators.find(id);
		if (it == animators.end())
			return NULL;
		return it->second;
	}

	Animation* get_animation(std::string id) {
		auto it = animations.find(id);
		if (it == animations.end())
			return NULL;
		return it->second;
	}

	void set_film(std::string id, AnimationFilm* anim) {
		bot_films.insert({ id,anim });
	}

	AnimationFilm* get_film(std::string id) {
		auto it = bot_films.find(id);
		if (it == bot_films.end())
			return NULL;
		return it->second;
	}

	void stop_animators() {
		for (auto it : animators) {
			it.second->Stop();
		}
	}

};
