#pragma once
#include "../Include/EngineDefines.h"
#include <iostream>
#include <cassert>
#include <functional>
#include <vector>

class AnimationFilm {
	std::vector<SDL_Rect> boxes;
	Bitmap bitmap = nullptr;
	std::string id;
public:
	byte GetTotalFrames(void) const
	{
		return boxes.size();
	}
	Bitmap GetBitmap(void) const { return bitmap; }
	auto GetId(void) const -> const std::string& { return id; }
	const SDL_Rect& GetFrameBox(byte frameNo) const
	{
		assert(boxes.size() > frameNo); return boxes[frameNo];
	}
	void DisplayFrame(Bitmap dest, const Point& at, byte frameNo) const
	{
		MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);
	}
	void SetBitmap(Bitmap b)
	{
		assert(!bitmap); bitmap = b;
	}
	void Append(const SDL_Rect& r) { boxes.push_back(r); }
	AnimationFilm(const std::string& _id) : id(_id) {}
	AnimationFilm(Bitmap, const std::vector<SDL_Rect>&, const std::string&);
};

class AnimationFilmHolder final {
public:
	using Parser = std::function<
		bool(std::list<AnimationFilm::Data>& output, const std::string& input)
	>;
	using EntryParser = std::function<
		int(// -1=error, 0=ended gracefully, else #chars read
			int startPos,
			const std::string& input,
			std::string& idOutput,
			std::string& pathOutput,
			std::vector<SDL_Rect>& rectsOutput
			)
	>;
private:
	using Films = std::map<std::string, AnimationFilm*>;
	Films films;
	BitmapLoader bitmaps; // only for loading of film bitmaps
	static AnimationFilmHolder holder; // singleton
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }
	static auto Get(void) -> const AnimationFilmHolder& { return holder; }
	void Load(const std::string& text, const EntryParser& entryParser);
	void Load(const std::string& text, const Parser& parser);
	void CleanUp(void);
	auto GetFilm(const std::string& id) -> const AnimationFilm* const;

	void AnimationFilmHolder::Load(const std::string& text, const EntryParser& entryParser) {
		int pos = 0;
		while (true) {
			std::string id, path;
			std::vector<SDL_Rect> rects;
			auto i = entryParser(pos, text, id, path, rects);
			assert(i >= 0);
			if (!i) return;
			pos += i;
			assert(!GetFilm(id));
			films[id] = new AnimationFilm(bitmaps.Load(path), rects, id);
		}
	}
	void AnimationFilmHolder::Load(const std::string& text, const Parser& parser) {
		std::list<AnimationFilm::Data> output;
		auto result = parser(output, text);
		assert(result);
		for (auto& entry : output) {
			assert(!GetFilm(entry.id));
			films[entry.id] = new AnimationFilm(
				bitmaps.Load(entry.path), entry.rects, entry.id
			);
		}
	}

	// .. continued
	void CleanUp(void) {
		for (auto& i : films)
			delete(i.second);
		films.clear();
	}
	auto GetFilm(const std::string& id) -> const AnimationFilm* const {
		auto i = films.find(id);
		return i != films.end() ? i->second : nullptr;
	}
};