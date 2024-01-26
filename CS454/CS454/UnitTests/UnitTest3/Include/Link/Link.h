#pragma once
#include "../Characters/Character.h"

class Link : public Character{
	public:
		static Link singleton;
	protected:
		int points=0;
		unsigned int lifes=3;
		bool haskey = false;
		int magic;

	public:
		/*set*/
		
		void setPoints(int newPoints) { points = newPoints; }
		void setLifes(unsigned int newLifes) { lifes = newLifes; }
		void setHasKey(bool newHasKey) { haskey = newHasKey; }
		void setMagic(int newMagic) { magic = newMagic; }

		/*get*/
		int getPoints() const { return points; }
		unsigned int getLifes() const { return lifes; }
		bool getHasKey() const { return haskey; }
		int getMagic() const { return magic; }
		
		static auto GetSingleton(void) -> Link&{
			return singleton;
		}

};