
#include "../../Include/initAnimationsSprites.h"

void init_elevator_animators(TileLayer* layer)
{
    /*ELEVATOR 1*/
    MovingAnimation* el_up = new MovingAnimation("elevator_up", 80, 0, 2, 40);
    MovingAnimation* el_down = new MovingAnimation("elevator_down", 80, 0, 2, 40);

    MovingAnimator* el_animator_up = new MovingAnimator("elevator.up", el_up);
    MovingAnimator* el_animator_down = new MovingAnimator("elevator.down", el_down);


    MovingAnimator* link_elev = new MovingAnimator("link.el", el_down);
    auto s = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator1_down");
    auto s_up = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator1_up");




    animator_init(s_up, el_animator_up, el_up, []() {}, []() {});
    animator_init(s, el_animator_down, el_down, [el_animator_up, el_animator_down]()
        {
            el_animator_up->Start(GetSystemTime());
        }, [s_up, s, layer]()
            {
                auto [x_up, y_up] = get_sprite_start_pos_scaled(s_up->GetTypeId());
                auto [x_d, y_d] = get_sprite_start_pos_scaled(s->GetTypeId());

                s_up->SetPos(x_up, y_up);
                s->SetPos(x_d, y_d);
                auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
                int scale = layer->get_scale();
                auto [dst_x, dst_y] = get_sprite_start_pos("Elevator2_down");
                link->SetPos(dst_x * scale, (dst_y - 15) * scale);
                link->setGridIgnore(false);
                link->setCanMove(true);
                link->GetGravityHandler().set_gravity_addicted(true);

                InputKeys::GetSingleton().layers_set((link->GetBox().x - link->get_layer_viewWin().w / 2) / scale, 0);
            });
    animator_init(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), link_elev, el_down, []() {}, []() {});

    /*ELAVATOR 2*/
    MovingAnimation* el2_up = new MovingAnimation("elevator2_up", 80, 0, -2, 40);
    MovingAnimation* el2_down = new MovingAnimation("elevator2_down", 80, 0, -2, 40);

    MovingAnimator* el2_animator_up = new MovingAnimator("elevator2.up", el2_up);
    MovingAnimator* el2_animator_down = new MovingAnimator("elevator2.down", el2_down);

    MovingAnimator* link2_elev = new MovingAnimator("link2.el", el2_down);
    auto s2 = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator2_down");
    auto s2_up = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator2_up");




    animator_init(s2_up, el2_animator_up, el2_up, []() {}, []() {});
    animator_init(s2, el2_animator_down, el2_down, [el2_animator_up, el2_animator_down]()
        {
            el2_animator_up->Start(GetSystemTime());
        }, [s2_up, s2, layer]()
            {
                auto [x_up, y_up] = get_sprite_start_pos_scaled(s2_up->GetTypeId());
                auto [x_d, y_d] = get_sprite_start_pos_scaled(s2->GetTypeId());

                s2_up->SetPos(x_up, y_up);
                s2->SetPos(x_d, y_d);
                auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
                int scale = layer->get_scale();
                auto [dst_x, dst_y] = get_sprite_start_pos("Elevator1_down");
                link->SetPos(dst_x * scale, (dst_y - 30) * scale);
                link->setCanMove(true);
                link->GetGravityHandler().set_gravity_addicted(true);
                link->setGridIgnore(false);

                //layer->SetViewWindow({ link->get_layer_viewWin().x - link->get_layer_viewWin().w / 2,link->get_layer_viewWin().y ,link->get_layer_viewWin().w,link->get_layer_viewWin().h });
                InputKeys::GetSingleton().layers_set((link->GetBox().x - link->get_layer_viewWin().w / 2) / scale, 0);
            });
    animator_init(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), link2_elev, el2_down, []() {}, []() {});
}

void init_elevators(TileLayer *layer) {
    init_elevator_animators(layer);
}