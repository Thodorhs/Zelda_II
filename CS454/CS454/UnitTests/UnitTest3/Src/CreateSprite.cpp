#include "../Include/CreateSprite.h"
#include "../Include/Link/Link.h"
#include "../Include/initAnimationsSprites.h"
#include "../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../Engine/Include/Util/SystemClock.h"
#include "../../../Engine/Include/Sprites/CollisionChecker.h"

void drop_point_action(Sprite* s1, Sprite* s2) {
    if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
        Link::GetSingleton().addPoints(50);
        s2->SetVisibility(false);
		//CollisionChecker::GetSingleton().Cancel(s1, s2);
		//s2->Destroy();
    }
}
void drop_big_point_action(Sprite* s1, Sprite* s2) {
    if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
        Link::GetSingleton().addPoints(200);
        s2->SetVisibility(false);
        //CollisionChecker::GetSingleton().Cancel(s1, s2);
        //s2->Destroy();
    }
}
void drop_blue_pot_action(Sprite* s1, Sprite* s2) {
    if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
        Link::GetSingleton().addMagic(16);
        s2->SetVisibility(false);
        CollisionChecker::GetSingleton().Cancel(s1, s2);
        s2->Destroy();
    }
}
void drop_red_pot_action(Sprite* s1, Sprite* s2) {
    if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
        Link::GetSingleton().addMagic(128);
        s2->SetVisibility(false);
        //CollisionChecker::GetSingleton().Cancel(s1, s2);
        //s2->Destroy();
    }
}
void key_action_boss(Sprite* s1, Sprite* s2) {
    if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
        if (s2->GetTypeId() == "final_key") {
            s2->SetVisibility(false);
            Link::GetSingleton().addKey(3);
			//CollisionChecker::GetSingleton().Cancel(s1, s2);
           // s2->Destroy();
        }
    }
}

Sprite* create_drop_sprite(Sprite* s, AnimationFilmHolder& holder, std::string film, int* x, TileLayer* layer) {
    *x = *x + 1;
    auto sprite = new Sprite(s->GetBox().x , s->GetBox().y-10, const_cast<AnimationFilm*>(holder.GetFilm(film)), s->GetTypeId() + film + std::to_string(*x));
    PrepareSpriteGravityHandler(layer, sprite);

    MovingAnimation* falling = new MovingAnimation("falling", 0, 0, 8, 40);
    MovingAnimator* animator = new MovingAnimator(sprite->GetTypeId() + "_falling", falling);
    animator->SetOnAction(animator->generic_animator_action(sprite));
    animator->SetOnStart(generic_start);
    animator->SetOnFinish(generic_stop);
    sprite->SetVisibility(true);

    sprite->GetGravityHandler().set_gravity_addicted(true);
    sprite->GetGravityHandler().SetOnStartFalling([animator, sprite]()
        {
            animator->Start(GetSystemTime());
        });

    sprite->GetGravityHandler().SetOnStopFalling([animator, sprite]()
        {
            animator->Stop();
            animator->Destroy();
        });
    sprite->SetMover(sprite->MakeSpriteGridLayerMover(layer, sprite));
    return sprite;
}
Sprite* create_drop_boss(Sprite* s, AnimationFilmHolder& holder, std::string film, TileLayer* layer) {
    auto sprite = new Sprite(s->GetBox().x, s->GetBox().y - 3, const_cast<AnimationFilm*>(holder.GetFilm(film)), "final_key");
    PrepareSpriteGravityHandler(layer, sprite);

    MovingAnimation* falling = new MovingAnimation("falling", 0, 0, 8, 40);
    MovingAnimator* animator = new MovingAnimator(sprite->GetTypeId() + "_falling", falling);
    animator->SetOnAction(animator->generic_animator_action(sprite));
    animator->SetOnStart(generic_start);
    animator->SetOnFinish(generic_stop);
    sprite->SetVisibility(true);

    sprite->GetGravityHandler().set_gravity_addicted(true);
    sprite->GetGravityHandler().SetOnStartFalling([animator, sprite]()
        {
            animator->Start(GetSystemTime());
        });

    sprite->GetGravityHandler().SetOnStopFalling([animator, sprite]()
        {
            animator->Stop();
            animator->Destroy();
        });
    sprite->SetMover(sprite->MakeSpriteGridLayerMover(layer, sprite));
    return sprite;
}

