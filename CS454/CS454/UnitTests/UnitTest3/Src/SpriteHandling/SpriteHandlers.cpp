#include "../../Include/SpriteHandling/SpriteHandlers.h"
#include "../../../../Engine/Include/Sprites/CollisionChecker.h"
#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../Include/Link/Link.h"
#include "../../Include/Characters/CharacterManager.h"
Link Link::singleton;
std::string crouch_films[] = { "Link.Crouch.left","Link.Crouch.right" };
std::string jump_films[] = { "Link.jump.left", "Link.jump.right" };

CharacterManager &cman = CharacterManager::GetSingleton();

void elevator_action1(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_s)) {
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator1.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link1.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void elevator_action2(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_w)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		animator_man.Get_by_Id("link.jump")->Stop();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator2.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link2.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 2");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void elevator_action3(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_s)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator3.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link3.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 3");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void elevator_action4(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_w)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		animator_man.Get_by_Id("link.jump")->Stop();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator4.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link4.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 4");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void elevator_action5(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_w)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		animator_man.Get_by_Id("link.jump")->Stop();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator5.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link5.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 6");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
	else if (InputKeys::GetSingleton().KeyPressed(SDLK_s)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator5.down_down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link5.el_down");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 6");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void elevator_action6(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_s)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		animator_man.Get_by_Id("link.jump")->Stop();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator6.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link6.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 6");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void elevator_action7(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_w)) {
		AnimatorManager& animator_man = AnimatorManager::GetSingleton();
		animator_man.Get_by_Id("link.jump")->Stop();
		s1->setCanMove(false);
		s1->setGridIgnore(true);
		s1->GetGravityHandler().set_gravity_addicted(false);
		auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator7.down");
		auto l = AnimatorManager::GetSingleton().Get_by_Id("link7.el");
		if (l->HasFinished() && e->HasFinished()) {
			pr_info("starting action 6");
			l->Start(GetSystemTime());
			e->Start(GetSystemTime());
		}
	}
}
void door_action(Sprite* s1, Sprite* s2){
	auto e = AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId());
	if (e->HasFinished()) {
		if (s2->GetTypeId() == "door1"&& Link::GetSingleton().haskey(0) ) {
			//CollisionChecker::GetSingleton().Cancel(s1, s2);
			Link::GetSingleton().removekey(0);
			e->Start(GetSystemTime());
			pr_info("rm key1");
		}
		else if (s2->GetTypeId() == "door2" && Link::GetSingleton().haskey(1) ) {
			//CollisionChecker::GetSingleton().Cancel(s1, s2);
			pr_info("rm key2");
			Link::GetSingleton().removekey(1);
			e->Start(GetSystemTime());
		}
		else if (s2->GetTypeId() == "door3" && Link::GetSingleton().haskey(2) ) {
			//CollisionChecker::GetSingleton().Cancel(s1, s2);
			pr_info("rm key3");
			Link::GetSingleton().removekey(2);
			e->Start(GetSystemTime());
		}
		else if (s2->GetTypeId() == "door4" && Link::GetSingleton().haskey(3) ) {
			//CollisionChecker::GetSingleton().Cancel(s1, s2);
			pr_info("rm key4");
			Link::GetSingleton().removekey(3);
			e->Start(GetSystemTime());
		}
			
	}	
}
void key_action(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_b)&&s2->IsVisible()) {
		if (s2->GetTypeId() == "key1") {
			s2->SetVisibility(false);
			Link::GetSingleton().addKey(0);
		}else if (s2->GetTypeId() == "key2") {
			s2->SetVisibility(false);
			Link::GetSingleton().addKey(1);
		}
		else if (s2->GetTypeId() == "key3") {
			s2->SetVisibility(false);
			Link::GetSingleton().addKey(2);
		}
		else if (s2->GetTypeId() == "key4") {
			s2->SetVisibility(false);
			Link::GetSingleton().addKey(3);
		}
		//s2->Destroy();
	}
}
void doll_action(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_b)&& s2->IsVisible()) {
		s2->SetVisibility(false);
		Link::GetSingleton().addLifes(1);
	}
}
void point_action(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_b)&& s2->IsVisible()) {
		s2->SetVisibility(false);
		Link::GetSingleton().addPoints(50);
	}
}
void blue_pot_action(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
		s2->SetVisibility(false);
		Link::GetSingleton().addMagic(16);
	}
}
void red_pot_action(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_b) && s2->IsVisible()) {
		s2->SetVisibility(false);
		Link::GetSingleton().addMagic(128);
	}
}
void end_key_action(Sprite* s1, Sprite* s2) {
	return;
}

void init_elevators() {
	auto names = get_elevator_names();
	for (auto& it : names) {
		SpriteManager::GetSingleton().Get_sprite_by_id(it)->GetGravityHandler().set_gravity_addicted(false);
		SpriteManager::GetSingleton().Get_sprite_by_id(it)->setGridIgnore(true);
	}
}

void create_and_register_sprites(TileLayer* layer)
{
	AnimationFilmHolder& holder = AnimationFilmHolder::getInstance();
	SpriteManager& manager = SpriteManager::GetSingleton();
	const Clipper clipper = MakeTileLayerClipper(layer);
	auto s_list = get_sprite_name_list();
	for (auto& it : s_list)
	{
		int id_pref = 0;
		if (get_sprite_type(it) == "projectile")
			continue;
		auto list = get_pos_list(it, layer->get_scale());

		for (auto& pos : list) {
			std::string id = id_pref == 0 ? it : it + std::to_string(id_pref);
			Sprite* sprite = new Sprite(pos.x, pos.y, const_cast<AnimationFilm*>(holder.GetFilm(get_sprite_initial_film(it))), id);
			auto f = sprite->MakeSpriteGridLayerMover(layer, sprite);
			sprite->SetMover(f);
			manager.Add(sprite);
			manager.AddtoMap(get_sprite_type(it), sprite);
			id_pref++;
		}

	}
	init_elevators();

}


void Guma_collission(Sprite* s1,Sprite *s2)
{
	
	pr_info("guma colision");
	if(cman.Get_by_Id(s2->GetTypeId(), "Guma") && !cman.Get_by_Id(s2->GetTypeId(),"Guma")->is_Hit() && cman.Get_by_Id(s2->GetTypeId(), "Guma")->IsAlive()){
		if((s1->GetFilm()->GetId() == "Link.Attack.left"||s1->GetFilm()->GetId() == "Link.Crouch.Attack.left")&&(s2->GetBox().x <= s1->GetBox().x)){
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			//cman.Get_by_Id(s2->GetTypeId())->
			if(s1->GetBox().x<=s2->GetBox().x){
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(1);
			} else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(-1);
			}
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}
		else if ((s1->GetFilm()->GetId() == "Link.Attack.right"||s1->GetFilm()->GetId() == "Link.Crouch.Attack.right") && (s2->GetBox().x >= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			if (s1->GetBox().x <= s2->GetBox().x) {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(1);
			}
			else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(-1);
			}
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}
	}
}

void Bot_collission(Sprite* s1, Sprite* s2)
{
	if (cman.Get_by_Id(s2->GetTypeId(), "Palace_bot")&& !cman.Get_by_Id(s2->GetTypeId(), "Palace_bot")->is_Hit() && cman.Get_by_Id(s2->GetTypeId(), "Palace_bot")->IsAlive()) {
		if ((s1->GetFilm()->GetId() == "Link.Attack.left" || s1->GetFilm()->GetId() == "Link.Crouch.Attack.left") && (s2->GetBox().x <= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			//cman.Get_by_Id(s2->GetTypeId())->
			if (s1->GetBox().x <= s2->GetBox().x) {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(1);
			}
			else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(-1);
			}
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}
		else if ((s1->GetFilm()->GetId() == "Link.Attack.right" || s1->GetFilm()->GetId() == "Link.Crouch.Attack.right") && (s2->GetBox().x >= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			if (s1->GetBox().x <= s2->GetBox().x) {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(1);
			}
			else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(-1);
			}
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}else if (Link::GetSingleton().can_hit(GetSystemTime(), 1000)) {
			Link::GetSingleton().damage(Link::GetSingleton().getdif());
			if(s1->GetBox().x<=s2->GetBox().x){
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s1->GetTypeId() + "_damage"))->SetDx(-1);
			} else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s1->GetTypeId() + "_damage"))->SetDx(1);
			}
			AnimatorManager::GetSingleton().Get_by_Id("Link_damage")->Start(GetSystemTime());
		}
	}
	pr_info("bot colision");
}
void Wosu_collission(Sprite* s1, Sprite* s2)
{
	std::string film =s1->GetFilm()->GetId();
	//std::string prevfilm = s1->GetprevFilm()->GetId();
	if (!cman.Get_by_Id(s2->GetTypeId(), "Wosu")->is_Hit()) {
		if ((film == "Link.Attack.left" || film == "Link.Crouch.Attack.left") && (s2->GetBox().x <= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			//cman.Get_by_Id(s2->GetTypeId())->
			if (s1->GetBox().x <= s2->GetBox().x) {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(1);
			}
			else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(-1);
			}
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}
		else if ((film == "Link.Attack.right" || film == "Link.Crouch.Attack.right") && (s2->GetBox().x >= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			if (s1->GetBox().x <= s2->GetBox().x) {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(1);
			}
			else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage"))->SetDx(-1);
			}
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}else if(Link::GetSingleton().can_hit(GetSystemTime(),1000) ){
			if (s1->GetBox().x <= s2->GetBox().x) {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s1->GetTypeId() + "_damage"))->SetDx(-1);
			}
			else {
				((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s1->GetTypeId() + "_damage"))->SetDx(1);
			}
			Link::GetSingleton().damage(Link::GetSingleton().getdif());
			AnimatorManager::GetSingleton().Get_by_Id("Link_damage")->Start(GetSystemTime());
		}
	}
	
	pr_info("col with wosu");
}
void Staflos_collission(Sprite* s1, Sprite* s2)
{
	if (cman.Get_by_Id(s2->GetTypeId(), "Staflos") && !cman.Get_by_Id(s2->GetTypeId(), "Staflos")->is_Hit() && cman.Get_by_Id(s2->GetTypeId(), "Staflos")->IsAlive()) {
		if ((s1->GetFilm()->GetId() == "Link.Crouch.Attack.left") && (s2->GetBox().x <= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			//cman.Get_by_Id(s2->GetTypeId())->
			pr_info("damage staflos");
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}
		else if (( s1->GetFilm()->GetId() == "Link.Crouch.Attack.right") && (s2->GetBox().x >= s1->GetBox().x)) {
			//cman.Get_by_Id(s2->GetTypeId())->setHit(true);
			pr_info("damage staflos");
			AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId() + "_damage")->Start(GetSystemTime());
		}
		else if (Link::GetSingleton().can_hit(GetSystemTime(), 1000)) {
			if (s1->GetFilm()->GetId() == "Link.Crouch.right"&&(s2->GetBox().x >= s1->GetBox().x)) {
				pr_info("parry");
				return;
			}
			else if (s1->GetFilm()->GetId() == "Link.Crouch.left" && (s2->GetBox().x <= s1->GetBox().x)) {
				pr_info("parry"); 
				return;
			}
			else if (s2->GetFilm()->GetId() == "Staflos.attack.right" || s2->GetFilm()->GetId() == "Staflos.attack.left" || s2->GetFilm()->GetId() == "Staflos.fall") {
				if (s1->GetBox().x <= s2->GetBox().x) {
					((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s1->GetTypeId() + "_damage"))->SetDx(-1);
				}
				else {
					((FrameRangeAnimator*)AnimatorManager::GetSingleton().Get_by_Id(s1->GetTypeId() + "_damage"))->SetDx(1);
				}
				Link::GetSingleton().damage(Link::GetSingleton().getdif()+2);
				AnimatorManager::GetSingleton().Get_by_Id("Link_damage")->Start(GetSystemTime());
			}	
		}
	}
	pr_info("Coll with staflos");
}



void register_guma_collisions(TileLayer *layer)
{
	CollisionChecker& col = CollisionChecker::GetSingleton();
	auto Gumas = SpriteManager::GetSingleton().GetTypeList("Guma");
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	for(auto& it : Gumas)
	{
		col.Register(link, it, Guma_collission);
	}
}

void register_staflos_collisions(TileLayer* layer)
{
	CollisionChecker& col = CollisionChecker::GetSingleton();
	auto Staflos = SpriteManager::GetSingleton().GetTypeList("Staflos");
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	for (auto& it : Staflos)
	{
		col.Register(link, it, Staflos_collission);
	}
}


void register_wosu_collisions(TileLayer* layer)
{
	CollisionChecker& col = CollisionChecker::GetSingleton();
	auto wosus = SpriteManager::GetSingleton().GetTypeList("Wosu");
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	for (auto& it : wosus)
	{
		col.Register(link, it, Wosu_collission);
	}
}



void register_bot_collisions(TileLayer* layer)
{
	CollisionChecker& col = CollisionChecker::GetSingleton();
	auto Bots = SpriteManager::GetSingleton().GetTypeList("Palace_bot");
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	for (auto& it : Bots)
	{
		col.Register(link, it,Bot_collission);
	}
}


void register_collisions(TileLayer* layer) {
	CollisionChecker& col = CollisionChecker::GetSingleton();
	SpriteManager& manager = SpriteManager::GetSingleton();
	//col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Guma"), [](Sprite* s1, Sprite* s2) {pr_error("collision"); });
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator1_down"), elevator_action1);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator2_down"), elevator_action2);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator3_down"), elevator_action3);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator4_down"), elevator_action4);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator5_down"), elevator_action5);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator6_down"), elevator_action6);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator7_down"), elevator_action7);
	for(auto i=1;i<5;i++){
		col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("door"+std::to_string(i)),door_action);
	}
	for (auto i = 1; i < 5; i++) {
		col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("key" + std::to_string(i)), key_action);
	}
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("doll1"), doll_action);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("points1"), point_action);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("points2"), point_action);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("blue_pot1"), blue_pot_action);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("blue_pot2"), blue_pot_action);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("red_pot1"), red_pot_action);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("end_key"), end_key_action);
	register_guma_collisions(layer);
	register_staflos_collisions(layer);
	register_wosu_collisions(layer);
	register_bot_collisions(layer);
}

void init_sprites(TileLayer* layer) {
	create_and_register_sprites(layer);
	register_collisions(layer);
}