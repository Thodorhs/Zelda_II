#pragma once
#include "Animator.h"
#include <set>
#include <assert.h>

class AnimatorManager {
private:
	std::set<Animator*> running, suspended;
	static AnimatorManager singleton;
	AnimatorManager(void) = default;
	AnimatorManager(const AnimatorManager&) = delete;
	AnimatorManager(AnimatorManager&&) = delete;
public:
	void Register(Animator* a)
	{
		assert(a->HasFinished()); suspended.insert(a);
	}
	void Cancel(Animator* a)
	{
		assert(a->HasFinished()); suspended.erase(a);
	}
	void MarkAsRunning(Animator* a)
	{
		assert(!a->HasFinished()); suspended.erase(a); running.insert(a);
	}
	void MarkAsSuspended(Animator* a)
	{
		assert(a->HasFinished()); running.erase(a); suspended.insert(a);
	}
	void Progress(timestamp_t currTime) {
		auto copied(running);
		for (auto* a : copied)
			a->Progress(currTime);
	}
	static auto GetSingleton(void) -> AnimatorManager& { return singleton; }
	static auto GetSingletonConst(void) -> const AnimatorManager& { return singleton; }
};
