#include "../../Include/initAnimationsSprites.h"


Animator::OnStart bot_jump_start(Sprite *b,MovingAnimator* fall,FrameRangeAnimator *move,int scale) {
	return ([b,fall,move,scale](Animator* anim)
		{
			//b->Move(5, 0);
			if (!fall->HasFinished()) {
				dynamic_cast<MovingAnimator*>(anim)->SetDy(0);
				dynamic_cast<MovingAnimator*>(anim)->SetDx(0);
			}
			else {
				dynamic_cast<MovingAnimator*>(anim)->SetDy(-scale * 8);
				dynamic_cast<MovingAnimator*>(anim)->SetDx(dynamic_cast<MovingAnimator*>(anim)->GetDx());
				dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(b->GetTypeId() + "_falling"))->SetDx(dynamic_cast<MovingAnimator*>(anim)->GetDx());
			}
			generic_start(anim);
		}
	);
}


Animator::OnFinish bot_jump_stop(FrameRangeAnimator *move,Sprite *b) {
	return ([move,b](Animator* anim)
		{
			
			move->Start(GetSystemTime());
			generic_stop(anim);
		}
	);
}


Animator::OnFinish bot_move_stop(MovingAnimator *jump) {
	return ([jump](Animator* anim)
		{
			
			jump->Start(GetSystemTime());
			generic_stop(anim);
		}
	);
}

void init_bot_animators(TileLayer* layer) {
	auto bots = SpriteManager::GetSingleton().GetTypeList("Palace_bot");
	FrameRangeAnimation* fr_bot = new FrameRangeAnimation("bot", 0, 1, 5, 0, 0, 200);
	MovingAnimation* bot_jump = new MovingAnimation("bot.jump", 5, 10, -layer->get_scale()*8, 45);

	for (auto& b : bots) {
		MovingAnimation* mv_an_clone = (MovingAnimation*)bot_jump->Clone();
		FrameRangeAnimation* fr_bot_clone = (FrameRangeAnimation*)fr_bot->Clone();
		MovingAnimator* bot_jump_an = new MovingAnimator(b->GetTypeId() + "_jump",mv_an_clone);
		FrameRangeAnimator* mv = new FrameRangeAnimator(b->GetTypeId() + "_move",fr_bot_clone);
		mv->SetOnAction(mv->generic_animator_action(b));
		mv->SetOnStart(generic_start);
		mv->SetOnFinish(bot_move_stop(bot_jump_an));

		MovingAnimator* fall = dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(b->GetTypeId() + "_falling"));
		fall->SetDelay(100);
		fall->SetDx(5);

		bot_jump_an->SetOnAction(bot_jump_an->generic_animator_action(b));
		bot_jump_an->SetOnStart(bot_jump_start(b,fall,mv,layer->get_scale()));
		bot_jump_an->SetOnFinish(bot_jump_stop(mv,b));	
		
	}
	fr_bot->Destroy();
	bot_jump->Destroy();
	//AnimatorManager::GetSingleton().Get_by_Id("Palace_bot_move")->Start(GetSystemTime());
	//AnimatorManager::GetSingleton().Get_by_Id("Palace_bot_jump")->Start(GetSystemTime());
}

void init_bot(TileLayer* layer) {
	init_bot_animators(layer);
}