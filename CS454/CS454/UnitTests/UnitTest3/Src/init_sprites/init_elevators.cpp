
#include "../../Include/initAnimationsSprites.h"
#include <string>

void init_elevator_animators(TileLayer* layer, int i, int dx) {
    pr_info("elevator" + std::to_string(i) + "_up");
    MovingAnimation* el_up = new MovingAnimation("elevator" + std::to_string(i) + "_up", 80, 0, dx, 10);
    MovingAnimation* el_down = new MovingAnimation("elevator" + std::to_string(i) + "_down", 80, 0, dx, 10);
    MovingAnimator* el_animator_up;
    MovingAnimator* el_animator_down;
    MovingAnimator* link_elev;
    if (dx == 2 && i == 5) {
        el_animator_up = new MovingAnimator("elevator" + std::to_string(i) + ".up_dowm", el_up);
        el_animator_down = new MovingAnimator("elevator" + std::to_string(i) + ".down_down", el_down);
        link_elev = new MovingAnimator("link" + std::to_string(i) + ".el_down", el_down);
    }
    else {
        el_animator_up = new MovingAnimator("elevator" + std::to_string(i) + ".up", el_up);
        el_animator_down = new MovingAnimator("elevator" + std::to_string(i) + ".down", el_down);
        link_elev = new MovingAnimator("link" + std::to_string(i) + ".el", el_down);
    }

    auto s = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator" + std::to_string(i) + "_down");
    auto s_up = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator" + std::to_string(i) + "_up");

    animator_init(s_up, el_animator_up, el_up, []() {}, []() {});
    animator_init(s, el_animator_down, el_down, [el_animator_up, el_animator_down]()
        {
            el_animator_up->Start(GetSystemTime());
        }, [s_up, s, layer, i, dx]()
            {
                auto [x_up, y_up] = get_sprite_start_pos_scaled(s_up->GetTypeId());
                auto [x_d, y_d] = get_sprite_start_pos_scaled(s->GetTypeId());

                s_up->SetPos(x_up, y_up);
                s->SetPos(x_d, y_d);
                auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
                int scale = layer->get_scale();
                SDL_Point p;
                if (i == 5) {
                    if (dx == -2) {
                        p = get_sprite_start_pos("Elevator" + std::to_string(i + 1) + "_down");
                    }
                    else {
                        p = get_sprite_start_pos("Elevator" + std::to_string(i + 2) + "_down");
                    }
                }
                else if (i == 6) {
                    p = get_sprite_start_pos("Elevator" + std::to_string(i - 1) + "_down");
                }
                else if (i == 7) {
                    p = get_sprite_start_pos("Elevator" + std::to_string(i - 2) + "_down");
                }
                else {
                    p = get_sprite_start_pos("Elevator" + std::to_string(i + dx / 2) + "_down");
                }
                link->SetPos(p.x * scale, (p.y - 30) * scale);
                link->setCanMove(true);
                link->GetGravityHandler().set_gravity_addicted(true);
                link->setGridIgnore(false);

                InputKeys::GetSingleton().layers_set((link->GetBox().x - link->get_layer_viewWin().w / 2) / scale, 0);
            });
    animator_init(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), link_elev, el_down, []() {}, []() {});
}

void init_elevators(TileLayer* layer) {
    init_elevator_animators(layer, 1, 2);
    init_elevator_animators(layer, 2, -2);
    init_elevator_animators(layer, 3, 2);
    init_elevator_animators(layer, 4, -2);
    init_elevator_animators(layer, 5, -2);
    init_elevator_animators(layer, 5, 2);
    init_elevator_animators(layer, 6, 2);
    init_elevator_animators(layer, 7, -2);
}