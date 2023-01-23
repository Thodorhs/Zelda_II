#pragma once
#include <map>
#include "../../../Engine/Include/Util/SystemClock.h"
#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../Engine/Include/KeyFrameAnimation/FilmParser.h"

#include "../../../Engine/Include/Animators/FrameRangeAnimator.h"


class Link_Class final {
private:
	std::map<std::string, Animator*> animators;
	std::map<std::string, Animation*>animations;
	static  Link_Class singleton;
public:

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


	static auto GetSingleton(void) -> Link_Class& { return singleton; }
	static auto GetSingletonConst(void) -> const Link_Class& { return singleton; }

	
};