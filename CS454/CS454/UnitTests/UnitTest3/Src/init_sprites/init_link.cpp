#include "../../Include/initAnimationsSprites.h"
std::string left_films[] = { "Link.Attack.left","Link.Run.left","Link.jump.left","Link.falling.left" ,
	"Link.damage.left","Link.Crouch.left","Link.Crouch.Attack.left"};
std::string right_films[] = { "Link.Attack.right","Link.Run.right","Link.jump.right","Link.falling.right",
	"Link.damage.right" ,"Link.Crouch.right","Link.Crouch.Attack.left"};
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



void fr_link_start(Animator *animator)
{
	generic_start(animator);
}

void fr_link_stop(Animator* animator)
{
	generic_stop(animator);
}


Animator::OnAction link_fr_action(Sprite* s) {
	return ([s](Animator* animator, const Animation& anim)
		{
			if (s->GetFilm()->GetId() == "Link.Run.left" || s->GetFilm()->GetId() == "Link.Run.right")
				FrameRange_Action_noSet(s, animator, (FrameRangeAnimation&)anim);
		}
	);
}





void init_link_move_animator(TileLayer* layer)
{
	auto scale = layer->get_scale();
	MovingAnimation* mv = new MovingAnimation("link.move", 4 * scale, 1, 0, scale);
	MovingAnimator* mv_an = new MovingAnimator("link.move", mv);
	Link_animators.push_back(mv_an);
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
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.frame.animation", 0, 4, 1, 0, 0, 75);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link", fr_animation);
	Link_animators.push_back(animator);

	MovingAnimation* jump = new MovingAnimation("link.jump", 3, 0, -layer->get_scale() * 16, 50);
	MovingAnimator* jump_anim = new MovingAnimator("link.jump", jump);
	Link_animators.push_back(jump_anim);

	FrameRangeAnimation* link_attack_animation = new FrameRangeAnimation("link.attack", 0, 3, 1, 0, 0, 90);
	FrameRangeAnimator* link_attack_animator = new FrameRangeAnimator("Link.Attack", link_attack_animation);
	Link_animators.push_back(link_attack_animator);

	animator_init(Link, link_attack_animator, link_attack_animation, [animator, Link, link_attack_animator]()
		{

			animator->Stop();

			if (is_left(Link->GetFilm()->GetId())) {
				Link->ChangeFilm("Link.Attack.left");
			}
			else {
				Link->ChangeFilm("Link.Attack.right");
			}

		}, [animator, Link]()
			{
				if (is_left(Link->GetFilm()->GetId()))
					Link->ChangeFilm("Link.Run.left");
				else
					Link->ChangeFilm("Link.Run.right");

			});
	//animator_init(Link, animator, fr_animation, []()
	//{
	//}, []() {})



	animator->SetOnAction(link_fr_action(Link));
	animator->SetOnStart(fr_link_start);
	animator->SetOnFinish(fr_link_stop);

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

			//AnimatorManager::GetSingleton().Get_by_Id("Link")->Stop();
			//for (auto& it : Link_animators)
				//it->Stop();
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

#include "../../Include/Link/Link.h"

void damage_start(Animator *animator)
{
	Link::GetSingleton().setHit(true);
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	auto sc = AnimatorManager::GetSingleton().Get_by_Id("scroll_right");
	auto sc_l = AnimatorManager::GetSingleton().Get_by_Id("scroll_left");
	for (auto& it : Link_animators) {
		if(it->Get_ID()!="Link_damage")
			it->Stop();
	}

	if (is_left(link->GetFilm()->GetId())) {
		link->ChangeFilm("Link.damage.left");
		link->setCanMove(false);
		//((FrameRangeAnimator*)animator)->SetDx(1);
		sc->Start(GetSystemTime());
	}
	else {
		link->ChangeFilm("Link.damage.right");
		link->setCanMove(false);
		//((FrameRangeAnimator*)animator)->SetDx(-1);
		sc_l->Start(GetSystemTime());
	}
	generic_start(animator);
}

void damage_stop(Animator *animator)
{
	Link::GetSingleton().setHit(false);
	auto link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	generic_stop(animator);
	if (is_left(link->GetFilm()->GetId())) {
		link->ChangeFilm("Link.Run.left");
	}
	else {
		link->ChangeFilm("Link.Run.right");
	}
	link->setCanMove(true);
}



void crouch_att_start(Animator *animator)
{
	AnimatorManager::GetSingleton().Get_by_Id("Link")->Stop();
	auto Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	auto id = Link->GetFilm()->GetId();
	if (id != "Link.Crouch.left" && id != "Link.Crouch.right") {
		pr_warning("trying to crouch attack while not crouched!");
		return;
	}

	if (id == "Link.Crouch.left") {
		Link->ChangeFilm("Link.Crouch.Attack.left");
	}
	else {
		Link->ChangeFilm("Link.Crouch.Attack.right");
	}
	generic_start(animator);
}

void crouch_att_stop(Animator *animator)
{
	auto Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");
	if (is_left(Link->GetFilm()->GetId()))
		Link->ChangeFilm("Link.Crouch.left");
	else
		Link->ChangeFilm("Link.Crouch.right");
	generic_stop(animator);
}


Animator::OnAction link_crattack_action(Sprite* s) {
	return ([s](Animator* animator, const Animation& anim)
		{
			if (s->GetFilm()->GetId() == "Link.Crouch.Attack.left" || s->GetFilm()->GetId() == "Link.Crouch.Attack.right")
				FrameRange_Action_noSet(s, animator, (FrameRangeAnimation&)anim);
		}
	);
}



void link_att_crouch()
{
	FrameRangeAnimation* link_attack_animation = new FrameRangeAnimation("link.attack", 0, 3, 1, 0, 0, 90);
	FrameRangeAnimator* link_attack_animator = new FrameRangeAnimator("Link.Attack.Crouch", link_attack_animation);
	Link_animators.push_back(link_attack_animator);
	auto Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");

	link_attack_animator->SetOnAction(link_crattack_action(Link));
	link_attack_animator->SetOnStart(crouch_att_start);
	link_attack_animator->SetOnFinish(crouch_att_stop);

}



void link_damage(TileLayer *layer)
{
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.damage", 0, 19, 1, 0, 0, 15);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link_damage", fr_animation);

	animator->SetOnAction(animator->generic_animator_action(SpriteManager::GetSingleton().Get_sprite_by_id("Link")));
	animator->SetOnStart(damage_start);
	animator->SetOnFinish(damage_stop);
	Link_animators.push_back(animator);
}
void shield_start(Animator *animator){
	Link::GetSingleton().use_shield();
	generic_start(animator);
	
}
void shield_finish(Animator *animator) {
	Link::GetSingleton().set_shield(false);
	generic_stop(animator);
}

void link_shield(TileLayer* layer)
{
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.shield", 0, 1, 1, 0, 0, 10000);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link_shield", fr_animation);

	animator->SetOnAction(animator->generic_animator_action(SpriteManager::GetSingleton().Get_sprite_by_id("Link")));
	animator->SetOnStart(shield_start);
	animator->SetOnFinish(shield_finish);
	Link_animators.push_back(animator);
}

void init_link(TileLayer* layer) {
	init_link_animators(layer);
	link_gravity(layer);
	link_damage(layer);
	link_att_crouch();
}