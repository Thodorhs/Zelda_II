#pragma once
#include <map>
#include "../../../Engine/Include/Util/SystemClock.h"
#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../Engine/Include/KeyFrameAnimation/FilmParser.h"

#include "../../../Engine/Include/Animators/FrameRangeAnimator.h"
class GameCharacters {
	private:
		std::string type;
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
		virtual void set_type(std::string type) { type = type; }
		virtual void set_id(std::string id) { id = id; }
		virtual std::string get_type() { return type; }
		virtual std::string get_id() { return id; }
	
};