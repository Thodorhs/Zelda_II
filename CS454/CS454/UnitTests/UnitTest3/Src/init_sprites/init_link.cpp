#include "../../Include/initAnimationsSprites.h"
std::string left_films[] = { "Link.Attack.left","Link.Run.left","Link.jump.left","Link.falling.left" };
std::string right_films[] = { "Link.Attack.right","Link.Run.right","Link.jump.right","Link.falling.right" };
std::vector<Animator*>Link_animators;

bool is_left(const std::string& id)
{
	for (auto& it : left_films)
	{
		if (id == it)
			return  true;
	}
	return false;
}

bool is_right(const std::string& id)
{
	for (auto& it : right_films)
	{
		if (id == it)
			return  true;
	}
	return false;
}

void init_link_move_animator(TileLayer* layer)
{
	auto scale = layer->get_scale();
	MovingAnimation* mv = new MovingAnimation("link.move", 4 * scale, 1, 0, scale);
	MovingAnimator* mv_an = new MovingAnimator("link.move", mv);
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	animator_init(link, mv_an, mv, [link,mv_an]() {
		if (!AnimatorManager::GetSingleton().Get_by_Id("Link_falling")->HasFinished())
			return;
		if (mv_an->GetDx() < 0) {
			link->ChangeFilm("Link.Run.left");
		}
		else {
			link->ChangeFilm("Link.Run.right");
		}

		}, []() {});
}

void init_link_scroll_anim(TileLayer* layer)
{
	auto scale = layer->get_scale();
	ScrollAnimation* an = new ScrollAnimation("sc", scale, 4);
	an->SetDx(1);
	ScrollAnimator* scroll_animator = new ScrollAnimator("scroll_right", an);


	ScrollAnimation* an_l = new ScrollAnimation("sc", scale, 4);
	an_l->SetDx(-1);

	ScrollAnimator* scroll_animator_l = new ScrollAnimator("scroll_left", an_l);
	animator_init(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), scroll_animator, an, []() {}, []() {});
	animator_init(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), scroll_animator_l, an_l, []() {}, []() {});

}


void init_link_animators(TileLayer* layer)
{
	Sprite* Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");

	//AnimatorManager& manager = AnimatorManager::GetSingleton();
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.frame.animation", 0, 4, 1, 0, 0, 100);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link", fr_animation);
	Link_animators.push_back(animator);

	MovingAnimation* jump = new MovingAnimation("link.jump", 3, 0, -layer->get_scale() * 16, 50);
	MovingAnimator* jump_anim = new MovingAnimator("link.jump", jump);
	Link_animators.push_back(jump_anim);

	FrameRangeAnimation* link_attack_animation = new FrameRangeAnimation("link.attack", 0, 2, 1, 0, 0, 80);
	FrameRangeAnimator* link_attack_animator = new FrameRangeAnimator("Link.Attack", link_attack_animation);
	Link_animators.push_back(link_attack_animator);

	animator_init(Link, link_attack_animator, link_attack_animation, [animator, Link, link_attack_animator]()
		{

			animator->Stop();

			if (is_left(Link->GetFilm()->GetId()))
				Link->ChangeFilm("Link.Attack.left");
			else
				Link->ChangeFilm("Link.Attack.right");

		}, [animator, Link]()
			{
				if (is_left(Link->GetFilm()->GetId()))
					Link->ChangeFilm("Link.Run.left");
				else
					Link->ChangeFilm("Link.Run.right");

			});
	animator_init(Link, animator, fr_animation, []() {}, []() {});
	animator_init(Link, jump_anim, jump, [animator, Link]()
		{

			animator->Stop();
			if (is_left(Link->GetFilm()->GetId()))
				Link->ChangeFilm("Link.jump.left");
			else
				Link->ChangeFilm("Link.jump.right");

		}, [Link, animator]()
			{
				animator->Stop();
				if (is_left(Link->GetFilm()->GetId()))
					Link->ChangeFilm("Link.falling.left");
				else
					Link->ChangeFilm("Link.falling.right");

			});

	init_link_move_animator(layer);
	init_link_scroll_anim(layer);
}



void link_gravity(TileLayer* layer) {
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	auto animator = AnimatorManager::GetSingleton().Get_by_Id("Link_falling");

	link->GetGravityHandler().SetOnStartFalling([animator, link]()
		{

			AnimatorManager::GetSingleton().Get_by_Id("Link")->Stop();
			
			if (is_left(link->GetFilm()->GetId()))
				link->ChangeFilm("Link.falling.left");
			else
				link->ChangeFilm("Link.falling.right");
			
			animator->Start(GetSystemTime());
		});

	
	link->GetGravityHandler().SetOnStopFalling([animator, link]()
		{
			
			if (is_left(link->GetFilm()->GetId()))
				link->ChangeFilm("Link.Run.left");
			else
				link->ChangeFilm("Link.Run.right");
			
			animator->Stop();
		});
}


void init_link(TileLayer* layer) {
	init_link_animators(layer);
	link_gravity(layer);
}