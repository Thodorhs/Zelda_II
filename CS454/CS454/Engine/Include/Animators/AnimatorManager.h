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
		assert(a);
		assert(a->HasFinished()); suspended.insert(a);
	}
    void TimeShift(unsigned dt) {
        for (auto* a : running)
            a->TimeShift(dt);
    }
	void Cancel(Animator* a)
	{
		assert(a);
		assert(a->HasFinished()); suspended.erase(a);
	}
	void MarkAsRunning(Animator* a)
	{
		assert(a);
		assert(!a->HasFinished());
		suspended.erase(a); running.insert(a);
	}
	void MarkAsSuspended(Animator* a)
	{
		assert(a);
		assert(a->HasFinished()); running.erase(a); suspended.insert(a);
	}
	void Progress(timestamp_t currTime) {
		auto copied(running);
		for (auto* a : copied) 
			a->Progress(currTime);
	}

	Animator* Get_by_Id_sus(const std::string& id) const
	{
		for(auto &it : suspended)
			if (it->Get_ID() == id)
				return it;
		return nullptr;
	}

	Animator* Get_by_Id_run(const std::string& id) const
	{
		for (auto& it : running)
			if (it->Get_ID() == id)
				return it;
		return nullptr;
	}

	Animator* Get_by_Id(const std::string& id) const
	{
		auto sus = Get_by_Id_sus(id);
		auto run = Get_by_Id_run(id);
		if (sus && run)
			assert(0);
		if (sus)
			return sus;
		if (run)
			return run;
		return nullptr;
			
	}

	static auto GetSingleton(void) -> AnimatorManager& { return singleton; }
	static auto GetSingletonConst(void) -> const AnimatorManager& { return singleton; }
};
