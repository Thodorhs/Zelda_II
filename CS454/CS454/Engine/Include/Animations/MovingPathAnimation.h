#pragma once
#include "Animation.h"
#include <vector>
struct PathEntry {
	int dx = 0, dy = 0;
	unsigned frame = 0;
	unsigned delay = 0;
	PathEntry(void) = default;
	PathEntry(const PathEntry&) = default;
	PathEntry(int _dx, int _dy, unsigned _fr, unsigned _del) : dx(_dx),dy(_dy),frame(_fr),delay(_del) {}
};

class MovingPathAnimation : public Animation {
public:
	using Path = std::vector<PathEntry>;
private:
	Path path;
	unsigned path_size;
public:


	unsigned GetReps() {
		return path_size;
	}

	int GetDelay(unsigned path_index) {
		return path[path_index].delay;
	}

	const int GetFrame(int path_index)const {
		return path[path_index].frame;
	}

	const int GetPathDx(int path_index)const {
		return path[path_index].dx;
	}
	const int GetPathDy(int path_index)const {
		return path[path_index].dy;
	}
	bool isForever() {
		return false;
	}


	const Path& GetPath(void) const { return path; }
	void SetPath(const Path& p) { path = p; }
	Animation* Clone(void) const override
	{
		return new MovingPathAnimation(id, path,path_size);
	}
	MovingPathAnimation(const std::string& _id, const Path& _path) :
		path(_path), Animation(id) {}

	MovingPathAnimation(const std::string& _id, const Path& _path,const unsigned size) :
		path(_path), Animation(id) ,path_size(size){}
};