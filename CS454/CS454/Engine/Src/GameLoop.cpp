#include "../Include/App.h"

void app::Game::MainLoop(void) {
	while (!IsFinished()) MainLoopIteration();
}

void app::Game::MainLoopIteration(void) {
	Render();
	Input();
	if (!IsPaused()) {
		ProgressAnimations();
		AI();
		Physics();
		CollisionChecking();
		CommitDestructions();
		//UserCode();
	}
}
