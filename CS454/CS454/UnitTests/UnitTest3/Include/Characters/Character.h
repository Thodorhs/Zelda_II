#include <string>

class Character
{
private:
	std::string Id;
	int health = 100;

public:
	void set_health(const int val) { health = val; }
	const int get_health()const { return health; }

	const std::string get_id() { return Id; }

	Character(std::string id) : Id(std::move(id)){}


};