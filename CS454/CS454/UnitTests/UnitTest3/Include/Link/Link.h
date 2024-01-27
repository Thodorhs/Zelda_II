#pragma once
#include "../Characters/Character.h"

class Link {
	private:
		Link(void) = default;
		Link(const Link&) = delete;
		Link(Link&&) = delete;
		static Link singleton;
	protected:
		int points=0;
		unsigned int lifes=3;
		//int keys = 0;
		bool keys[4];
		int magic;

	public:
		/*set*/
		
		void setPoints(int newPoints) { points = newPoints; }
		void setLifes(unsigned int newLifes) { lifes = newLifes; }
		void addKey(int i) { keys[i] = true; }
		void setMagic(int newMagic) { magic = newMagic; }
		void removekey(int i) { keys[i]=false; }
		bool haskey(int i) { return keys[i]; }
		/*get*/
		int getPoints() const { return points; }
		unsigned int getLifes() const { return lifes; }
		bool getKeys() const { return keys; }
		int getMagic() const { return magic; }
		
		
		static auto GetSingleton(void) -> Link& {
			return singleton;
		}
};
