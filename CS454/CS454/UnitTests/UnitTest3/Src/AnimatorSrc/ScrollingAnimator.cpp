#include "../../../../Engine/Include/Animators/ScrollingAnimator.h"

void ScrollAnimator::Progress(timestamp_t currTime) {
	
		while (currTime > lastTime && (currTime - lastTime) >= anim->GetScroll()[0].delay) {
			lastTime += anim->GetScroll()[0].delay;
			NotifyAction(*anim);
			
				
		}
		state = ANIMATOR_FINISHED;
		NotifyStopped();
		return;
}

void ScrollAction(TileLayer &ActionLayer,TileLayer &HorizonLayer) {
	float Scrolldx = 1.0;
	float Scrolldy = 0;
	ActionLayer.ScrollWithBoundsCheck(Scrolldx, 0);
	HorizonLayer.ScrollWithBoundsCheck(Scrolldx, 0);

}