#pragma once
#include "GameCharacters.h"
class Guma : public GameCharacter {
private:
    std::map<std::string, Animator*> animators;
    std::map<std::string, Animation*>animations;
    std::map<std::string, AnimationFilm*> guma_films;
    Character_t type;
    std::string id;
    Sprite* current;
    using Fire = std::function<void(void)>;
    Fire fire;
public:

    Guma() { id = "Guma"; }
    void set_fire(std::function<void(void)>f) override { fire = f; }
    void fire_action() override { fire(); }
    Character_t get_type() { return type; }
    std::string get_id() { return id; }
    void set_type(Character_t type) { type = type; }
    void set_id(std::string id) { id = id; }
    void print_character() { std::cout << "Guma!" << "\n"; }

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
        guma_films.insert({ id,anim });
    }

    AnimationFilm* get_film(std::string id) {
        auto it = guma_films.find(id);
        if (it == guma_films.end())
            return NULL;
        return it->second;
    }

    void stop_animators() {
        for (auto it : animators) {
            it.second->Stop();
        }
    }


};