#pragma once
#include "../Characters/Character.h"

class Link {
private:
	Link(void) = default;
	Link(const Link&) = delete;
	Link(Link&&) = delete;
	static Link singleton;
protected:
	int health = 100;
	int lifes = 3;
	int magic = 100;
	bool keys[4];
	int points = 0;
	bool alive = true;
	bool isHit = false;
public:
	/*set*/
	void setHit(const bool val) { isHit = val; }
	const bool is_Hit()const { return isHit; }
	void setPoints(int newPoints) { points = newPoints; }
	void setLifes(int newLifes) { lifes = newLifes; }
	void addKey(int i) { keys[i] = true; }
	void setMagic(int newMagic) { magic = newMagic; }
	void removekey(int i) { keys[i] = false; }
	/*if it returns true it means that link needs to spawn at a checkpoint*/
	bool damage(int d) {
		if (health - d < 0) {
			if (lifes - 1 == 0) {
				alive = false;
				return false;
			}
			else {
				lifes--;
				health = 100;
				return true;
			}
		}
		health = health - d;
		return false;
	}
	/*get*/
		bool haskey(int i) { return keys[i]; }
		bool isAlive() { return alive; }
		int getHealth(){return health;}
		int getPoints() const { return points; }
		int getLifes() const { return lifes; }
		bool getKeys() const { return keys; }
		int getMagic() const { return magic; }
		
		void cant_hit(timestamp_t currTime, int ms);
		static auto GetSingleton(void) -> Link& {
			return singleton;
		}
};
