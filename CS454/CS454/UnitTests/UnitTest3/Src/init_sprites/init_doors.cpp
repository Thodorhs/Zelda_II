#include "../../Include/initAnimationsSprites.h"
#include <string>

void init_door_animators(int i, FrameRangeAnimation* door_animation) {

    
    FrameRangeAnimator* dooranimator = new FrameRangeAnimator("door" + std::to_string(i), door_animation);
       
    auto s = SpriteManager::GetSingleton().Get_sprite_by_id("door" + std::to_string(i));

    animator_init(s, dooranimator, door_animation, 
    [dooranimator]()
    {},
    [s,dooranimator, door_animation]()
    {
        dooranimator->Destroy();
        s->Destroy();
    });
}

void init_doors(){
    FrameRangeAnimation* door_animation = new FrameRangeAnimation("door",0, 18, 1, 0, 0, 60);
    init_door_animators(1,door_animation);
    init_door_animators(2,door_animation);
	init_door_animators(3,door_animation);
	init_door_animators(4,door_animation);
}