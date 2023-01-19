#include "../../../Engine/Include/AnimationFilmHolder.h"

void AnimationFilmHolder::Load(const std::string& text, const EntryParser& entryParser, SDL_Renderer* GameRenderer) {
	int pos = 0;
	while (true) {
		std::string id, path;
		std::vector<SDL_Rect> rects;
		auto i = entryParser(pos, text, id, path, rects);
		assert(i >= 0);
		//if (!i) return;
		pos += i;
		assert(!GetFilm(id));
		films[id] = new AnimationFilm(bitmaps.Load(path, GameRenderer), rects, id);
		if (!i) return; //just for test delete later
	}

}
void AnimationFilmHolder::Load(const std::string& text, const Parser& parser, SDL_Renderer* GameRenderer) {
	std::list<AnimationFilm::Data> output;
	auto result = parser(output, text);
	assert(result);
	for (auto& entry : output) {
		assert(!GetFilm(entry.id));
		films[entry.id] = new AnimationFilm(
			bitmaps.Load(entry.path, GameRenderer), entry.rects, entry.id
		);
	}
}


void AnimationFilmHolder::CleanUp(void) {
	for (auto& i : films)
		delete(i.second);
	films.clear();
}
auto AnimationFilmHolder::GetFilm(const std::string& id) -> const AnimationFilm* const {
	auto i = films.find(id);
	return i != films.end() ? i->second : nullptr;
}