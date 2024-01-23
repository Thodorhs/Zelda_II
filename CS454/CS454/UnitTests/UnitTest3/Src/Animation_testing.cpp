
#include "../Include/SpriteHandling/SpriteHandlers.h"
#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../Engine/Include/Util/SystemClock.h"


SpriteManager SpriteManager::singleton;

std::string left_films[] = {"Link.Attack.left","Link.Run.left","Link.jump.left","Link.falling.left"};
std::string right_films[] = { "Link.Attack.right","Link.Run.right","Link.jump.right","Link.falling.right" };

std::vector<Animator*>Link_animators;
bool is_left(const std::string &id)
{
	for(auto &it : left_films)
	{
		if (id == it)
			return  true;
	}
	return false;
}

bool is_right(const std::string& id)
{
	for (auto &it : right_films)
	{
		if (id == it)
			return  true;
	}
	return false;
}

bool Link_animators_Notfinished()
{
		AnimatorManager& animator_manager = AnimatorManager::GetSingleton();
		return (!animator_manager.Get_by_Id("Link")->HasFinished() ||
			!animator_manager.Get_by_Id("link.jump")->HasFinished() ||
			!animator_manager.Get_by_Id("Link_falling")->HasFinished() ||
			!animator_manager.Get_by_Id("Link.Attack")->HasFinished());
}

bool move_Link(int dx,int dy)
{
	AnimatorManager& animator_manager = AnimatorManager::GetSingleton();
	SpriteManager& s_manager = SpriteManager::GetSingleton();
	if (auto sprite = s_manager.Get_sprite_by_id("Link")) {
		auto [x, y,h,w] = sprite->GetBox();
		sprite->Move(dx, dy);
		if (!Link_animators_Notfinished()) {
			
			animator_manager.Get_by_Id("Link")->Start(GetSystemTime());
		}
		
		return (x != sprite->GetBox().x || y != sprite->GetBox().y);
	}
	return  false;
}

void render_sprite(SDL_Renderer* renderer, TileLayer* layer)
{
	for (SpriteManager& s_manager = SpriteManager::GetSingleton(); auto it : s_manager.GetDisplayList())
	{
		if (it){
			SDL_Rect dst = { 0,0,layer->GetViewWindow().w,layer->GetViewWindow().h };
			it->Display(dst, MakeTileLayerClipper(layer),renderer);
		}
	}
}

template<typename s_Action ,typename f_Action>
void animator_init(Sprite* sprite,Animator *animator,Animation* fr_animation,s_Action s,f_Action f)
{
	
	animator->SetOnAction(animator->generic_animator_action(sprite));
	animator->SetOnStart([s](Animator* animator)
		{
			
			AnimatorManager::GetSingleton().MarkAsRunning(animator);
			s();
		});
	animator->SetOnFinish([f](Animator* animator)
		{
			
			AnimatorManager::GetSingleton().MarkAsSuspended(animator);
			f();
		});
}



void animators_testing(TileLayer *layer)
{
	Sprite* Link = SpriteManager::GetSingleton().Get_sprite_by_id("Link");

	//AnimatorManager& manager = AnimatorManager::GetSingleton();
	FrameRangeAnimation* fr_animation = new  FrameRangeAnimation("link.frame.animation", 0, 4,1 , 0, 0, 150);
	FrameRangeAnimator* animator = new FrameRangeAnimator("Link",fr_animation);
	Link_animators.push_back(animator);

	MovingAnimation* jump = new MovingAnimation("link.jump", 1, 0, -10, 20);
	MovingAnimator* jump_anim = new MovingAnimator("link.jump", jump);
	Link_animators.push_back(jump_anim);

	FrameRangeAnimation* link_attack_animation = new FrameRangeAnimation("link.attack", 0, 2, 1, 0, 0, 80);
	FrameRangeAnimator* link_attack_animator = new FrameRangeAnimator("Link.Attack", link_attack_animation);
	Link_animators.push_back(link_attack_animator);

	animator_init(Link, link_attack_animator, link_attack_animation, [animator,Link,link_attack_animator]()
	{

		animator->Stop();
		
		if (is_left(Link->GetFilm()->GetId()))
			Link->ChangeFilm("Link.Attack.left");
		else
			Link->ChangeFilm("Link.Attack.right");

	}, [animator,Link]()
	{
			if (is_left(Link->GetFilm()->GetId()))
				Link->ChangeFilm("Link.Run.left");
			else
				Link->ChangeFilm("Link.Run.right");
		
	});
	animator_init(Link, animator, fr_animation, []() {}, []() { });
	animator_init(Link, jump_anim, jump,[animator,Link]()
	{
			animator->Stop();
			if(is_left(Link->GetFilm()->GetId()))
				Link->ChangeFilm("Link.jump.left");
			else
				Link->ChangeFilm("Link.jump.right");
			
	},[Link,animator]()
	{
			animator->Stop();
			if (is_left(Link->GetFilm()->GetId()))
				Link->ChangeFilm("Link.falling.left");
			else
				Link->ChangeFilm("Link.falling.right");
	});
}

void generic_gravity_init(TileLayer* layer)
{
	MovingAnimation* falling = new MovingAnimation("falling", 0, 0, 5, 40);
	SpriteManager& sprite_manager = SpriteManager::GetSingleton();
	for(auto &it : sprite_manager.GetDisplayList())
	{
		MovingAnimator* animator = new MovingAnimator(it->GetTypeId() + "_falling", falling);
		animator_init(it, animator, falling,[](){},[](){});
		if (it->GetTypeId() == "Link")
			Link_animators.push_back(animator);
		PrepareSpriteGravityHandler(layer, it);
		it->GetGravityHandler().SetOnStartFalling([animator,it]()
			{
				
				if(it->GetTypeId()=="Link")
				{
					AnimatorManager::GetSingleton().Get_by_Id("Link")->Stop();
					if (is_left(it->GetFilm()->GetId()))
						it->ChangeFilm("Link.falling.left");
					else
						it->ChangeFilm("Link.falling.right");
				}
				animator->Start(GetSystemTime());
			});

		it->GetGravityHandler().SetOnStopFalling([animator,it]()
			{
				animator->Stop();
				if (it->GetTypeId()=="Link") {
					if (is_left(it->GetFilm()->GetId()))
						it->ChangeFilm("Link.Run.left");
					else
						it->ChangeFilm("Link.Run.right");
				}
			});
	}

}



void gravity_test(TileLayer *layer)
{
	SpriteManager& s_manager = SpriteManager::GetSingleton();
	auto s = s_manager.Get_sprite_by_id("Link");
	AnimatorManager& animator_man = AnimatorManager::GetSingleton();
	auto animator = animator_man.Get_by_Id(s->GetTypeId()+"_falling");
	PrepareSpriteGravityHandler(layer, s);
	s->GetGravityHandler().SetOnStartFalling([animator]()
		{
			animator->Start(GetSystemTime());
		});

	s->GetGravityHandler().SetOnStopFalling([animator]()
		{
			animator->Stop();
		});
}


void init_elevator_animators()
{
	MovingAnimation* el_up = new MovingAnimation("elevator_up", 2, 0, -5, 40);
	MovingAnimation* el_down = new MovingAnimation("elevator_down", 1, 0, 5, 100);

	MovingAnimator* el_animator_up = new MovingAnimator("elevator.up", el_up);
	MovingAnimator* el_animator_down = new MovingAnimator("elevator.down", el_down);


	MovingAnimator* link_elev = new MovingAnimator("link.el", el_down);
	auto s = SpriteManager::GetSingleton().Get_sprite_by_id("Elevator1_up_down");
	animator_init(s, el_animator_down, el_down, []() {}, []() {});
	animator_init(SpriteManager::GetSingleton().Get_sprite_by_id("Link"), link_elev, el_down, []() {}, []() {});

	
}


void init_tests(SDL_Renderer* renderer,TileLayer* layer) {
	pr_info("testing!!");
	
	init_sprites(layer);
	animators_testing(layer);
	generic_gravity_init(layer);
	init_elevator_animators();
	SpriteManager::GetSingleton().Get_sprite_by_id("Guma")->Move(0,1);
	
}