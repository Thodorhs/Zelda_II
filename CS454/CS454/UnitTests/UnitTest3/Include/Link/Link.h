#pragma once

class Link final{
	public:
		static Link singleton;
	protected:
		int health=100;
		int points=0;
		unsigned int lifes=3;
		bool haskey = false;
		int magic;

	public:
		/*set*/
		void setHealth(int newHealth) { health = newHealth; }
		void setPoints(int newPoints) { points = newPoints; }
		void setLifes(unsigned int newLifes) { lifes = newLifes; }
		void setHasKey(bool newHasKey) { haskey = newHasKey; }
		void setMagic(int newMagic) { magic = newMagic; }

		/*get*/
		int getHealth() const { return health; }
		int getPoints() const { return points; }
		unsigned int getLifes() const { return lifes; }
		bool getHasKey() const { return haskey; }
		int getMagic() const { return magic; }
		
		static auto GetSingleton(void) -> Link&{
			return singleton;
		}

};