#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../../Engine/Include/Sprites/SpriteHelpers.h"
#include "../../../../Engine/Include/Util//SystemClock.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../../Engine/Include/Sprites/SpriteManager.h"
#include "../../Include/Characters/Guma.h"
#include "../../Include/Characters/PalaceBot.h"
#include <string>


CharacterManager CharacterManager::singleton;

using SList = std::list<Sprite*>;

void guma_char_start(Character *g)
{
	
	AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move")->Start(GetSystemTime());
}


void guma_char_stop(Character *g)
{
	AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move")->Destroy();
	g->Destroy();
}

void guma_char_action(Character *g)
{
	Sprite* li = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	Sprite* gu = SpriteManager::GetSingleton().Get_sprite_by_id(g->get_id());
	int lx = li->GetBox().x;
	int gx = gu->GetBox().x;
	FrameRangeAnimator* an=dynamic_cast<FrameRangeAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move"));
	FrameRangeAnimator* pr = dynamic_cast<FrameRangeAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_proj"));
	pr_info(std::to_string(lx)+" "+ std::to_string(gx));
	int dx = 5;
	if (lx > gx) {
		gu->ChangeFilm("Guma_right");
		if(lx-gx>200){
			an->SetDx(dx);
			pr->SetDx(dx);
		}
		else{
			an->SetDx(-dx);
			pr->SetDx(dx);
		}
		
	} else if (lx < gx) {
		gu->ChangeFilm("Guma_left");
		if (gx - lx > 200) {
			an->SetDx(-dx);
			pr->SetDx(-dx);
		}
		else {
			an->SetDx(dx);
			pr->SetDx(-dx);
		}
	}
}



/****BOT******/
void bot_char_start(Character* g)
{

	AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move")->Start(GetSystemTime());
}


void bot_char_stop(Character* g)
{
	AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move")->Destroy();
	g->Destroy();
}

void bot_char_action(Character* b)
{
	Sprite* li = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	Sprite* bo = SpriteManager::GetSingleton().Get_sprite_by_id(b->get_id());
	int lx = li->GetBox().x;
	int bx = bo->GetBox().x;
	MovingAnimator* an = dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(b->get_id() + "_jump"));
	pr_info(std::to_string(lx) + " " + std::to_string(bx));
	int dx = 10;
	if (lx > bx) {
		an->SetDx(dx);
	}
	else if (lx < bx) {
		an->SetDx(-dx);
	}
}
	





void register_gumas(SList gumas) {
	for (auto& it : gumas) {
		Guma* c = new Guma(it->GetTypeId(), { it->GetBox().x,it->GetBox().y });
		CharacterManager::GetSingleton().Register(c, c->get_type());
		c->SetOnStart(guma_char_start);
		c->SetOnStop(guma_char_stop);
		c->SetOnAction(guma_char_action);
	}
	
}

void register_bots(SList bots) {
	for (auto& it : bots) {
		PalaceBot* c = new PalaceBot(it->GetTypeId(), { it->GetBox().x,it->GetBox().y });
		CharacterManager::GetSingleton().Register(c, c->get_type());
		c->SetOnStart(bot_char_start);
		c->SetOnStop(bot_char_stop);
		c->SetOnAction(bot_char_action);
	}
}

void register_Link(Sprite *s) {
	
}


void init_characters() {
	auto gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	auto link  = SpriteManager::GetSingleton().GetTypeList("Link").begin();
	auto bots = SpriteManager::GetSingleton().GetTypeList("Palace_bot");
	
	register_Link(*link);
	register_bots(bots);
	register_gumas(gumas);
}