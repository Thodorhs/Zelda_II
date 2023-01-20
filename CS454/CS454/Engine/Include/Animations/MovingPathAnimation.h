#pragma once
#include "Animation.h"

struct PathEntry {
	int dx = 0, dy = 0;
	unsigned frame = 0;
	unsigned delay = 0;
	PathEntry(void) = default;
	PathEntry(const PathEntry&) = default;
};

class MovingPathAnimation : public Animation {
public:
	using Path = std::vector<PathEntry>;
private:
	Path path;
public:
	const Path& GetPath(void) const { return path; }
	void SetPath(const Path& p) { path = p; }
	Animation* Clone(void) const override
	{
		return new MovingPathAnimation(id, path);
	}
	MovingPathAnimation(const std::string& _id, const Path& _path) :
		path(_path), Animation(id) {}
};