#include "../../Include/initAnimationsSprites.h"
#include <string>


void init_door_animators(int i, FrameRangeAnimation* door_animation, TileLayer* layer) {

    
    FrameRangeAnimator* dooranimator = new FrameRangeAnimator("door" + std::to_string(i), door_animation);
       
    auto s = SpriteManager::GetSingleton().Get_sprite_by_id("door" + std::to_string(i));

    animator_init(s, dooranimator, door_animation, 
    [](){},
    [s,dooranimator, layer,i]()
    {
			if (i == 1) {
				layer->get_grid_layer().setGridTile(10, 195, 0);
				layer->get_grid_layer().setGridTile(11, 195, 0);
				layer->get_grid_layer().setGridTile(12, 195, 0);
			}
			else if (i == 2) {
				layer->get_grid_layer().setGridTile(10, 394, 0);
				layer->get_grid_layer().setGridTile(11, 394, 0);
				layer->get_grid_layer().setGridTile(12, 394, 0);
			}
			else if (i == 3) {
				layer->get_grid_layer().setGridTile(11, 767, 0);
				layer->get_grid_layer().setGridTile(12, 767, 0);
				layer->get_grid_layer().setGridTile(13, 767, 0);
			}
			else if (i == 4) {
				layer->get_grid_layer().setGridTile(11, 860, 0);
				layer->get_grid_layer().setGridTile(12, 860, 0);
				layer->get_grid_layer().setGridTile(13, 860, 0);
			}
		s->SetVisibility(false);
		//dooranimator->Stop();
        //s->Destroy();
        //dooranimator->Destroy();
    });
}

void init_doors(TileLayer* layer){
    FrameRangeAnimation* door_animation = new FrameRangeAnimation("door",0, 18, 1, 0, 0, 60);
    init_door_animators(1,door_animation, layer);
    init_door_animators(2,door_animation, layer);
	init_door_animators(3,door_animation, layer);
	init_door_animators(4,door_animation, layer);
}