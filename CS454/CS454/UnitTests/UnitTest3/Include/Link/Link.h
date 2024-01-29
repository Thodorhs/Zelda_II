#pragma once
#include "../Characters/Character.h"
typedef uint64_t timestamp_t;
class Link {
private:
	Link(void) = default;
	Link(const Link&) = delete;
	Link(Link&&) = delete;
	static Link singleton;
protected:
	unsigned int difficulty = 8;
	int health = 100;
	int lifes = 3;
	int magic = 200;
	bool keys[4];
	int points = 0;
	bool alive = true;
	bool isHit = false;
	int delay = 200;
	uint64_t last_time;
public:
	/*set*/
	void setHit(const bool val) { isHit = val; }
	const bool is_Hit()const { return isHit; }
	void addPoints(int newPoints) { points += newPoints; }
	void addLifes(int newLifes) { lifes += newLifes; }
	void addKey(int i) { keys[i] = true; }
	void addMagic(int newMagic) { 
		if (magic + newMagic <= 200) {
			magic += newMagic;
		}
		else {
			magic = 200;
		}
	}
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
		unsigned int getdif() { return difficulty; }
		bool haskey(int i) { return keys[i]; }
		bool isAlive() { return alive; }
		int getHealth(){return health;}
		int getPoints() const { return points; }
		int getLifes() const { return lifes; }
		bool getKeys() const { return keys; }
		int getMagic() const { return magic; }
		
		bool can_hit(timestamp_t currTime, int ms)
		{
			if(!isHit && currTime > last_time+ms)
			{
				last_time = currTime;
				return true;
			}
			return false;
		}
		static auto GetSingleton(void) -> Link& {
			return singleton;
		}
};
