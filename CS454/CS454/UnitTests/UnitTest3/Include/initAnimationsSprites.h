#pragma once
#include "SDL.h"


#include "../Include/SpriteHandling/SpriteHandlers.h"
#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../Engine/Include/Animators/ScrollingAnimator.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../../Engine/Include/Util/SystemClock.h"
void init_animations_sprites(SDL_Renderer* renderer, TileLayer* layer);
void render_sprite(SDL_Renderer* renderer, TileLayer* layer);
void move_Link(void);
extern void init_elevators(TileLayer* layer);
extern void init_link(TileLayer* layer);
extern void init_guma(TileLayer* layer);
extern void init_bot(TileLayer* layer);
extern void init_doors(TileLayer* layer);
extern void init_wosus(TileLayer* layer);
extern void init_staflos(TileLayer* layer);
extern void init_mazura(TileLayer* layer);
extern void init_characters();


bool Link_animators_Notfinished();
template<typename s_Action, typename f_Action>
void animator_init(Sprite* sprite, Animator* animator, Animation* fr_animation, s_Action s, f_Action f)
{

	animator->SetOnAction(animator->generic_animator_action(sprite));
	animator->SetOnStart([s](Animator* animator)
		{

			AnimatorManager::GetSingleton().MarkAsRunning(animator);
			s();
		});
	animator->SetOnFinish([f](Animator* animator)
		{

			AnimatorManager::GetSingleton().MarkAsSuspended(animator);
			f();
		});
}
inline void generic_start(Animator* animator) {
	AnimatorManager::GetSingleton().MarkAsRunning(animator);
}

inline void generic_stop(Animator* animator) {
	AnimatorManager::GetSingleton().MarkAsSuspended(animator);
}

