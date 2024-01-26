#include "../../Include/SpriteHandling/SpriteHandlers.h"
#include "../../../../Engine/Include/Sprites/CollisionChecker.h"
#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/GameLoopFuncs/Input.h"
#include "../../Include/Link/Link.h"
Link Link::singleton;
std::string crouch_films[] = { "Link.Crouch.left","Link.Crouch.right" };
std::string jump_films[] = { "Link.jump.left", "Link.jump.right" };

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
CollisionChecker::Action door_action(TileLayer* layer){

	return([layer](Sprite* s1,Sprite* s2) {
		auto e = AnimatorManager::GetSingleton().Get_by_Id(s2->GetTypeId());
		if (e->HasFinished() && Link::GetSingleton().haskey()) {
			Link::GetSingleton().removekey();
			e->Start(GetSystemTime());
			if (s2->GetTypeId() == "door1") {
				layer->get_grid_layer().setGridTile(10, 195, 0);
				layer->get_grid_layer().setGridTile(11, 195, 0);
				layer->get_grid_layer().setGridTile(12, 195, 0);
			}	
		}
		});
}
void key_action(Sprite* s1, Sprite* s2) {
	if (InputKeys::GetSingleton().KeyPressed(SDLK_b)) {
		s2->Destroy();
		Link::GetSingleton().addKey(1);
	}
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
void register_collisions(TileLayer* layer) {
	CollisionChecker& col = CollisionChecker::GetSingleton();
	SpriteManager& manager = SpriteManager::GetSingleton();
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Guma"), [](Sprite* s1, Sprite* s2) {pr_error("collision"); });
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator1_down"), elevator_action1);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator2_down"), elevator_action2);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator3_down"), elevator_action3);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator4_down"), elevator_action4);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator5_down"), elevator_action5);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator6_down"), elevator_action6);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator7_down"), elevator_action7);
	for(auto i=1;i<5;i++){
		col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("door"+std::to_string(i)),door_action(layer));
	}
	for (auto i = 1; i < 5; i++) {
		col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("key" + std::to_string(i)), key_action);
	}
}

void init_sprites(TileLayer* layer) {
	create_and_register_sprites(layer);
	register_collisions(layer);
}