#pragma once

#include "BitmapLoader.h"
#include "AnimationFilm.h"


class AnimationFilmHolder final {
public:
	using Parser = std::function<
		bool(std::list<AnimationFilm::Data>& output, const std::string& path)
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
	static AnimationFilmHolder& getInstance() { return FilmHolder_Instance; }

	void Load(const std::string& text, const EntryParser& entryParser, SDL_Renderer* GameRenderer);
	void Load(const std::string& text, const Parser& parser, SDL_Renderer* GameRenderer);
	void CleanUp(void);
	auto GetFilm(const std::string& id) -> const AnimationFilm* const;

private:
	using Films = std::map<std::string, AnimationFilm*>;
	Films films;
	BitmapLoader bitmaps; // only for loading of film bitmaps
	static AnimationFilmHolder FilmHolder_Instance; // singleton
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }
	static auto Get(void) -> const AnimationFilmHolder& { return FilmHolder_Instance; }

};