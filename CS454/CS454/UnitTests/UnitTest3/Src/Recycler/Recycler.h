#pragma once
#include <iostream>
#include <stack>
#include "../Link_test/Guma.h"
#include "../Link_test/Wosu.h"
#include "../Link_test/GreatPalaceBot.h"
template <class T> class Recycled {// turn any class to green (recycle friendly)
protected:
	static std::stack<typename T*> recycler;
	static T* top_and_pop(void)
	{
		auto* x = recycler.top(); recycler.pop(); return x;
	}
public:
	template <class ... Types> static T* New(Types ... args) {
		if (recycler.empty())
			return new T(args...); // automatic propagation of any args
		else
			return new (top_and_pop()) T(args...); // reusing …
	}
	void Delete(void)
	{
		this->~T(); recycler.push(this);
	}
};
