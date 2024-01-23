#pragma once
#include "../Sprites/Sprite.h"
#include "../TileLayer.h"
#include "../Animators/Animator.h"
#include "../Animations/Animation.h"
#include "../Util/SystemClock.h"

#include "SDL.h"
#include <map>
#include <functional>

class InputKeys {

private:
    static InputKeys singleton;
    bool DpyGrid=false;
    bool is_running = false;
    std::map<SDL_Keycode, bool> pressed_keys;
    std::map<SDL_Keycode, bool> prevpressed_keys;
 
    bool CanJump = false;
    SDL_Rect ViewWin;
    Uint64 last=0;
    int distanceJumped = 0;
    int maxdistancejump = 350* (-8);
    int LinkSpeed = 5;
    int LinkJump = 8;
    int timer_interval = 100;
    TileLayer* Action_Layer;
    TileLayer* Horizon_Layer;
    TileLayer* Backround_Layer;
    Render* global_render_vars;

public:
    void setlayersinput(TileLayer* Action_Laye, TileLayer* Horizon_Laye, TileLayer* Backround_Laye){ 
        Action_Layer= Action_Laye;
        Horizon_Layer= Horizon_Laye;
        Backround_Layer= Backround_Laye;
    }
    bool CanDpyGrid() { return DpyGrid; }
    void updatePrev() { prevpressed_keys = pressed_keys; }
    bool isKeyPressed(SDL_Keycode keyCode) { return (pressed_keys[keyCode] == true); }
    void set_is_running(bool is_runnin) { is_running = is_runnin; }
    bool get_is_running() { return is_running; }
    bool isKeyReleased(SDL_Keycode keyCode) { return (pressed_keys[keyCode] == false); }
    static auto GetSingleton(void) -> InputKeys& { return singleton; }
    void setglobal_render_vars(Render* render_vars) { global_render_vars = render_vars; }
    void init_key_map();
    void InputRead();
    void update_press(SDL_Keycode code, bool state);
    //void InputExecution(Link_Class& Link, TileLayer& ActionLayer, TileLayer& HorizonLayer, GridLayer& GameGrid, bool& mouse_down);
    //void MoveWindowWithLink(Link_Class& link, float Scrolldx, int& dx);
    //bool CanJumpCheck(Link_Class& Link, GridLayer& GameGrid);
    //bool SetAction(Link_Class& Link, std::string StateCheck, std::string film, auto animator, auto animation, unsigned delay, int dx, int dy, float Scrolldx);
    //void LinkAction(auto animation, auto animator, unsigned delay, int dx, int dy);
    void move_horizon();
    void move_pixels_x(int pixels);
	void move_pixels_y(int pixels);
	void move();

    bool KeyPressed(SDL_Keycode code);
    bool KeyReleased(SDL_Keycode code);
    bool KeyDown(SDL_Keycode code);
};

