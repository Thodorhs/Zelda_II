#include "../Include/KeyFrameAnimation/AnimationFilmHolder.h"

void AnimationFilmHolder::Load(const std::string& conf_path, const Parser& parser, SDL_Renderer* GameRenderer) {
	std::list<AnimationFilm::Data> output;
	auto result = parser(output, conf_path);
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