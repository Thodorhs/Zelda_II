#include "SDL.h"
#pragma once

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


