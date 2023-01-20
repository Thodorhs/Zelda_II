#pragma once
#include <iostream>

class Animation {
protected:
	std::string id;
public:
	const std::string& GetId(void) { return id; }
	void SetId(const std::string& _id);
	virtual Animation* Clone(void) const = 0;
	Animation(const std::string& _id) : id(_id) {}
	virtual ~Animation() {}
};
