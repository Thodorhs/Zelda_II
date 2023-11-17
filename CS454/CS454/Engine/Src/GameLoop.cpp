#include "../Include/App.h"

void app::Game::MainLoop(void) {
	while (!IsFinished()) MainLoopIteration();
}

void app::Game::MainLoopIteration(void) {
	clock_t beginFrame = clock();
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
	clock_t endFrame = clock();
	deltaTime += endFrame - beginFrame;
	frames++;

	//if you really want FPS
	if (clockToMilliseconds(deltaTime) > 1000.0) { //every second
		frameRate = (double)frames;
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);
			std::cout << "CPU time was:" << averageFrameTimeMilliseconds << std::endl;
	}
}
