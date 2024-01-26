#include <string>

class Character
{
private:
	std::string Id;
	int health = 100;
	std::string type;

public:
	void set_health(const int val) { health = val; }
	const int get_health()const { return health; }

	const std::string get_id() { return Id; }
	const std::string get_type() { return type; }

	Character(std::string id) : Id(std::move(id)){}
	Character(std::string id,std::string type) : Id(std::move(id)), type(std::move(type)){}


};