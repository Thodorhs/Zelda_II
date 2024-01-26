#pragma once
#include <iostream>
#include "../Util/DestructionManager.h"
class Animation : public LatelyDestroyable {
protected:
	std::string id;
public:
	const std::string& GetId(void) { return id; }
	void SetId(const std::string& _id);
	virtual Animation* Clone(void) const = 0;
	Animation(const std::string& _id) : id(_id) {}
	virtual ~Animation() {}
};