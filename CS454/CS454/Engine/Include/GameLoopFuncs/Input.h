#pragma once
#include "../../../UnitTests/UnitTest3/Src/Link_test/Link.h"
#include "../Sprites/Sprite.h"
#include "../Grid/GridLayer.h"
#include "../TileLayer.h"
#include "../Animators/Animator.h"
#include "../Animations/Animation.h"

#include "SDL.h"
#include <map>

class InputKeys {
private:
    static InputKeys singleton;
    std::map<SDL_Keycode, bool> keyState;
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
    void InputExecution(Link_Class& link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, SDL_Rect& movingrect, bool& mouse_down);
    void LinkAction(auto animation, auto animator, int dx, int dy);
    static auto GetSingleton(void) -> InputKeys& { return singleton; }
};

