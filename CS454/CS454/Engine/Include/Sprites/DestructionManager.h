#pragma once
class LatelyDestroyable;
class DestructionManager {
	std::list<LatelyDestroyable*> dead;
	static DestructionManager singleton;
public:
	void Register(LatelyDestroyable* d);
	void Commit(void);
	static auto Get(void) -> DestructionManager& { return singleton; }
};
class LatelyDestroyable {
protected:
	friend class DestructionManager;
	bool alive = true;
	bool dying = false;
	virtual ~LatelyDestroyable() { assert(dying); }
	void Delete(void);
public:
	void set_alive(bool state) { alive = state; }
	bool IsAlive(void) const { return alive; }
	void Destroy(void) {
		if (alive) {
			alive = false;
			DestructionManager::Get().Register(this);
		}
	}
	LatelyDestroyable(void) = default;
};
