#include "../../Include/SpriteHandling/SpriteHandlers.h"
#include "../../../../Engine/Include/Sprites/CollisionChecker.h"
#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/GameLoopFuncs/Input.h"

std::string crouch_films[] = { "Link.Crouch.left","Link.Crouch.right" };
std::string jump_films[] = { "Link.jump.left", "Link.jump.right" };

void elevator_action1(Sprite *s1,Sprite *s2) {
	for (auto& it : crouch_films)
	{
		if (InputKeys::GetSingleton().KeyPressed(SDLK_s)) {
			//AnimatorManager& animator_man = AnimatorManager::GetSingleton();
			//animator_man.Get_by_Id("link.jump")->Stop();
			
			s1->setCanMove(false);
			s1->setGridIgnore(true);
			//s2->setGridIgnore(true);
			s1->GetGravityHandler().set_gravity_addicted(false);
			
			auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator.down");
			auto l = AnimatorManager::GetSingleton().Get_by_Id("link.el");

			if (l->HasFinished() && e->HasFinished()) {
				pr_info("starting action");
				l->Start(GetSystemTime());
				e->Start(GetSystemTime());
			}
			break;
		}
			
	}
}

void elevator_action2(Sprite* s1, Sprite* s2) {
	for (auto& it : jump_films)
	{
		if (InputKeys::GetSingleton().KeyPressed(SDLK_w)) {
			AnimatorManager& animator_man = AnimatorManager::GetSingleton();
			animator_man.Get_by_Id("link.jump")->Stop();
			s1->setCanMove(false);
			s1->setGridIgnore(true);
			//s2->setGridIgnore(true);
			s1->GetGravityHandler().set_gravity_addicted(false);

			auto e = AnimatorManager::GetSingleton().Get_by_Id("elevator2.down");
			auto l = AnimatorManager::GetSingleton().Get_by_Id("link2.el");

			if (l->HasFinished() && e->HasFinished()) {
				pr_info("starting action 2");
				l->Start(GetSystemTime());
				e->Start(GetSystemTime());
			}
			break;
		}

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
		auto [x, y] = get_sprite_start_pos(it);
		x *= layer->get_scale();
		y *= layer->get_scale();
		Sprite* sprite = new Sprite(x, y, const_cast<AnimationFilm*>(holder.GetFilm(get_sprite_initial_film(it))), it);
		auto f = sprite->MakeSpriteGridLayerMover(layer, sprite);
		sprite->SetMover(f);

		manager.Add(sprite);
	}
	init_elevators();

}
void register_collisions(){
	CollisionChecker& col = CollisionChecker::GetSingleton();
	SpriteManager& manager = SpriteManager::GetSingleton();
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Guma"), [](Sprite *s1,Sprite *s2) {pr_error("collision"); });
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator1_down"), elevator_action1);
	col.Register(manager.Get_sprite_by_id("Link"), manager.Get_sprite_by_id("Elevator2_down"), elevator_action2);
}

void init_sprites(TileLayer* layer) {
	create_and_register_sprites(layer);
	register_collisions();
}