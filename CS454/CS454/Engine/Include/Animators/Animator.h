#pragma once
#include "../Animations/Animation.h"
#include "../Sprites/Sprite.h"
#include <functional>



typedef uint64_t timestamp_t;
enum animatorstate_t {
	ANIMATOR_FINISHED = 0, ANIMATOR_RUNNING = 1, ANIMATOR_STOPPED = 2
};
class Animator  : public LatelyDestroyable{
public:
	using animator_action = std::function<void(Animator*, const Animation&)>;
	using OnFinish = std::function<void(Animator*)>;
	using OnStart = std::function<void(Animator*)>;
	using OnAction = std::function<void(Animator*, const Animation&)>;
protected:
	std::string id;
	timestamp_t lastTime = 0;
	animatorstate_t state = ANIMATOR_FINISHED;
	OnFinish onFinish;
	OnStart onStart;
	OnAction onAction;
	void NotifyStopped(void);
	void NotifyStarted(void);
	void NotifyAction(const Animation& anim);
	void Finish(bool isForced = false);
public:
	void Stop(void);
	virtual void Start(timestamp_t) = 0;

	virtual auto generic_animator_action(Sprite *s) -> animator_action = 0;

	bool HasFinished(void) const { return state != ANIMATOR_RUNNING; }
	virtual void TimeShift(timestamp_t offset);
	virtual void Progress(timestamp_t currTime) = 0;
	virtual std::string Get_ID() const = 0;
	template <typename Tfunc> void SetOnFinish(const Tfunc& f) { onFinish = f; }
	template <typename Tfunc> void SetOnStart(const Tfunc& f) { onStart = f; }
	template <typename Tfunc> void SetOnAction(const Tfunc& f) { onAction = f; }
	Animator(void);
	Animator(const Animator&) = delete;
	Animator(Animator&&) = delete;
	virtual ~Animator();
};
