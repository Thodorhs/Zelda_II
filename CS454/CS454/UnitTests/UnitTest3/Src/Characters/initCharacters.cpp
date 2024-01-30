#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../../Engine/Include/Sprites/SpriteHelpers.h"
#include "../../../../Engine/Include/Util//SystemClock.h"
#include "../../Include/Characters/CharacterManager.h"
#include "../../../Engine/Include/Sprites/SpriteManager.h"
#include "../../Include/Characters/Guma.h"
#include "../../Include/Characters/PalaceBot.h"
#include "../../Include/Characters/Staflos.h"
#include "../../Include/Characters/Wosu.h"
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
	//g->Destroy();
}

void guma_char_action(Character *g)
{
	if(g->is_Hit() || !g->is_Alive())
		return;
	Sprite* li = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	Sprite* gu = SpriteManager::GetSingleton().Get_sprite_by_id(g->get_id());
	int lx = li->GetBox().x;
	int gx = gu->GetBox().x;
	FrameRangeAnimator* an=dynamic_cast<FrameRangeAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move"));
	FrameRangeAnimator* pr = dynamic_cast<FrameRangeAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_proj"));
	
	int dx = 5;
	if (lx > gx) {
		gu->ChangeFilm("Guma_right");
		if(lx-gx>200){
			an->SetDx(dx);
			//if(pr->GetCurrRep() > 0)
				//pr->SetDx(dx);
		}
		else{
			an->SetDx(-dx);
			//if (pr->GetCurrRep() > 0)
				//pr->SetDx(dx);
		}
		
	} else if (lx < gx) {
		gu->ChangeFilm("Guma_left");
		if (gx - lx > 200) {
			an->SetDx(-dx);
			//if(pr->GetCurrRep()>0)
				//pr->SetDx(-dx);
		}
		else {
			an->SetDx(dx);
			//if(pr->GetCurrRep()>0)
				//pr->SetDx(-dx);
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
	//g->Destroy();
}

void bot_char_action(Character* b)
{
	Sprite* li = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	Sprite* bo = SpriteManager::GetSingleton().Get_sprite_by_id(b->get_id());
	int lx = li->GetBox().x;
	int bx = bo->GetBox().x;
	MovingAnimator* an = dynamic_cast<MovingAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(b->get_id() + "_jump"));
	//pr_info(std::to_string(lx) + " " + std::to_string(bx));
	int dx = 10;
	if (lx > bx) {
		an->SetDx(dx);
	}
	else if (lx < bx) {
		an->SetDx(-dx);
	}
}
	
/*****END BOT**********/


/********STAFLOS*******/


void staflos_char_start(Character* c)
{
	SpriteManager::GetSingleton().Get_sprite_by_id(c->get_id())->Move(0, 1);
	SpriteManager::GetSingleton().Get_sprite_by_id(c->get_id())->SetVisibility(true);
	
}


void staflos_char_stop(Character* c)
{
	AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_move")->Destroy();
	//c->Destroy();
}

void staflos_char_action(Character* c)
{
	if(!c->is_Alive())
		return;
	auto fall = AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_falling");
	auto mv = AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_move");
	auto att = AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_attack");
	Sprite* li = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	Sprite* st = SpriteManager::GetSingleton().Get_sprite_by_id(c->get_id());
	if(fall->HasFinished() && mv->HasFinished() && att->HasFinished() && !c->is_Hit() ){
		AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_move")->Start(GetSystemTime());
		FrameRangeAnimator* an = dynamic_cast<FrameRangeAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_move"));
		FrameRangeAnimator* attack = dynamic_cast<FrameRangeAnimator*>(AnimatorManager::GetSingleton().Get_by_Id(c->get_id() + "_attack"));
		int lx = li->GetBox().x;
		int sx = st->GetBox().x;

		int dx = 5;
		if (lx > sx) {
		st->ChangeFilm("Staflos.walk.right");
			if(lx-sx<80){
				if (rand() % 2 == 1) {
					attack->SetDx(dx);
					attack->Start(GetSystemTime());
				}
			}else{
				an->SetDx(dx);
			}
		}
		else if (lx < sx) {
		st->ChangeFilm("Staflos.walk.left");
			if (sx-lx<80) {
				if (rand() % 2 == 1) {
					attack->SetDx(-dx);
					attack->Start(GetSystemTime());
				}
			}else{
				an->SetDx(-dx);
			}
		}
	}
}


/********END STAFLOS******/

/**********WOSU***********/

void wosu_char_start(Character* g)
{

	AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move")->Start(GetSystemTime());
}


void wosu_char_stop(Character* g)
{
	AnimatorManager::GetSingleton().Get_by_Id(g->get_id() + "_move")->Destroy();
	//g->Destroy();
}

void wosu_char_action(Character* b)
{
	if (b->is_Hit())
		return;
	auto fr =AnimatorManager::GetSingleton().Get_by_Id(b->get_id() + "_framerange");
	auto mv = AnimatorManager::GetSingleton().Get_by_Id(b->get_id() + "_move");
	
	if (mv->HasFinished()) {
		mv->Start(GetSystemTime());
	}
	if (fr->HasFinished()) {
		fr->Start(GetSystemTime());
	}
}


/********ENDWOSU***********/

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

void register_staflos(SList staflos)
{
	for (auto& it : staflos) {
		Staflos* c = new Staflos(it->GetTypeId(), { it->GetBox().x,it->GetBox().y });
		CharacterManager::GetSingleton().Register(c, c->get_type());
		c->SetOnStart(staflos_char_start);
		c->SetOnStop(staflos_char_stop);
		c->SetOnAction(staflos_char_action);
	}
}


void register_wosus(SList wosus)
{
	for (auto& it : wosus) {
		Wosu* c = new Wosu(it->GetTypeId(), { it->GetBox().x,it->GetBox().y });
		CharacterManager::GetSingleton().Register(c, c->get_type());
		c->SetOnStart(wosu_char_start);
		c->SetOnStop(wosu_char_stop);
		c->SetOnAction(wosu_char_action);
	}
}


void init_characters() {
	auto gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	auto link  = SpriteManager::GetSingleton().GetTypeList("Link").begin();
	auto bots = SpriteManager::GetSingleton().GetTypeList("Palace_bot");
	auto staflos = SpriteManager::GetSingleton().GetTypeList("Staflos");
	auto wosus = SpriteManager::GetSingleton().GetTypeList("Wosu");

	
	register_Link(*link);
	register_bots(bots);
	register_gumas(gumas);
	register_staflos(staflos);
	register_wosus(wosus);
	
}