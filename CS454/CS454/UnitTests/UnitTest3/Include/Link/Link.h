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
		int keys = 0;
		int magic;

	public:
		/*set*/
		
		void setPoints(int newPoints) { points = newPoints; }
		void setLifes(unsigned int newLifes) { lifes = newLifes; }
		void addKey(int newkey) { keys += newkey; }
		void setMagic(int newMagic) { magic = newMagic; }
		void removekey() { keys--; }
		bool haskey() { return keys > 0; }
		/*get*/
		int getPoints() const { return points; }
		unsigned int getLifes() const { return lifes; }
		bool getKeys() const { return keys; }
		int getMagic() const { return magic; }
		
		
		static auto GetSingleton(void) -> Link& {
			return singleton;
		}
};
