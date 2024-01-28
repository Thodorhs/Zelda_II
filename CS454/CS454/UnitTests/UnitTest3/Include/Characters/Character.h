#pragma once
#include <functional>
#include <string>

#include "SDL_rect.h"
#include  "../../../../Engine/Include/Util/DestructionManager.h"
class Character : public LatelyDestroyable
{
public:
	using OnStart = std::function<void(Character*)>;
	using OnFinish = std::function<void(Character*)>;
	using OnAction = std::function<void(Character*)>;

protected:
	std::string Id;
	int health = 100;
	std::string type;
	bool isActive = false;
	bool isRunning = false;
	OnStart onStart;
	OnFinish onStop;
	OnAction onAction;
	void NotifyStarted(void);
	void NotifyStopped(void);
	void NotifyAction(void);
	SDL_Point start_pos;
public:
	virtual void progress_character() = 0;

	const bool is_Active() { return isActive; }
	const bool is_Running() { return isRunning; }
	const bool is_Alive() { return health > 0; }
	void setActive(const bool val) { isActive = val; }


	const std::string get_id() { return Id; }
	const std::string get_type() { return type; }
	const int get_health() { return health; }
	SDL_Point get_start_pos() { return start_pos; }


	virtual void Start() = 0;
	virtual void Stop() = 0;

	template<typename  Tfunc> void SetOnStart(const Tfunc& f) { onStart = f; }
	template<typename  Tfunc> void SetOnStop(const Tfunc& f) { onStop = f; }
	template<typename  Tfunc> void SetOnAction(const Tfunc& f) { onAction = f; }
	Character(void) = default;
	Character(std::string id) : Id(std::move(id)){}
	Character(std::string id,std::string type) : Id(std::move(id)), type(std::move(type)){}
	
	Character(const Character&) = delete;
	Character(Character&&) = delete;
};
