#pragma once
#include "../../../UnitTests/UnitTest3/Src/Link_test/Link.h"
#include "../Sprites/Sprite.h"
#include "../Grid/GridLayer.h"
#include "../TileLayer.h"
#include "../Animators/Animator.h"
#include "../Animations/Animation.h"
#include "../Util/SystemClock.h"

#include "SDL.h"
#include <map>

#define MAXDISTANCEJUMP  300*(-8)
class InputKeys {
private:
    static InputKeys singleton;
    std::map<SDL_Keycode, bool> keyState;
    int distanceJumped = 0;
    bool CanJump = false;
public:
    void SetKeyState(SDL_Keycode eventkey, bool value) {
        keyState[eventkey] = value;
    }

    bool isKeyPressed(SDL_Keycode keyCode) {
        return (keyState[keyCode] == true);
    }

    bool isKeyReleased(SDL_Keycode keyCode) {
        return (keyState[keyCode] == false);
    }

    void InputRead(bool& is_running);
    void InputExecution(Link_Class& Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& mouse_down);
    bool CanJumpCheck(Link_Class& Link, GridLayer& GameGrid);
    void SetAction(Link_Class& Link, std::string StateCheck, std::string film, auto animator, auto animation, unsigned delay, int dx, int dy);
    void LinkAction(auto animation, auto animator, unsigned delay, int dx, int dy);
    static auto GetSingleton(void) -> InputKeys& { return singleton; }
};

