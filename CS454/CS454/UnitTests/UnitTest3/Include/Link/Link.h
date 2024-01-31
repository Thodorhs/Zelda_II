#pragma once
#include "../Characters/Character.h"
#include "../../../Engine/Include/Util/Print.h"
#include "../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../Engine/Include/Util/SystemClock.h"
#include "../SoundManager/SoundManager.h"
typedef uint64_t timestamp_t;
class Link {
private:
	Link(void) = default;
	Link(const Link&) = delete;
	Link(Link&&) = delete;
	static Link singleton;
protected:
	unsigned int difficulty = 13;
	int health = 100;
	int lifes = 100;
	int magic = 200;
	bool keys[4];
	int points = 0;
	bool alive = true;
	bool isHit = false;
	int delay = 200;
	int dps = 8;
	uint64_t last_time;
	bool shield = false;
	bool isOnBoss = false;
public:

	void setOnBoss(bool val) { isOnBoss = val; }
	bool inBoss() { return isOnBoss; }

	/*set*/
	void use_shield() { 
		if (magic - 32 >= 0) {
			pr_info("activating shield");
			shield = true;
			magic -= 32;
		}else{
			pr_info("Not enough magic");
		}
	}
	void heal(){
		SoundManager::get_singleton().play_sfx("AOL_Spell.wav", 0, 2);
		if (magic - 70 >= 0) {
			magic -= 70;
			if(health +75>=100){
				health = 100;
			}else{
				health += 75;
			}
		}
	}
	void set_shield(bool s) { shield = s; }
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
		if(shield){
			d = d / 2;
		}
		if (health - d < 0) {
			if (lifes - 1 == 0) {
				AnimatorManager::GetSingleton().Get_by_Id("game_over")->Start(GetSystemTime());
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
		if (health <= 25) {
			SoundManager::get_singleton().play_sfx("AOL_LowHealth.wav", 0, 2);
		}
		else {
			SoundManager::get_singleton().play_sfx("AOL_Hurt.wav", 0, 2);
		}

		return false;
	}
	/*get*/

	int get_dps() { return dps; }
	unsigned int getdif() { return difficulty; }
	bool haskey(int i) { return keys[i]; }
	bool isAlive() { return alive; }
	int getHealth() { return health; }
	int getPoints() const { return points; }
	int getLifes() const { return lifes; }
	bool getKeys() const { return keys; }
	int getMagic() const { return magic; }
	bool getshield() { return shield; }
		
		bool can_hit(timestamp_t currTime, int ms)
		{
			if(!isHit && currTime > last_time+ms)
			{
				last_time = currTime;
				return true;
			}
			return false;
		}
        /*void start_shield(timestamp_t currTime, int ms)
        {
            if (shield && currTime > last_time + ms)
            {
                last_time = currTime;
                //return true;
            }
            //return false;
        }*/
		static auto GetSingleton(void) -> Link& {
			return singleton;
		}
};
