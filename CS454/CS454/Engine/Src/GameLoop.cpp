#include "../Include/App.h"
#include "../Include/Util/SystemClock.h"
SystemClock& s_clock = SystemClock::Get();

void app::Game::MainLoop(void) {
	while (!IsFinished()) MainLoopIteration();
}

void app::Game::MainLoopIteration(void) {
	clock_t beginFrame = clock();
	s_clock.Update();
	Input();
	if (s_clock.GetDeltaTime() >= (1.0f / 60)) {
		Render();
		if (!IsPaused()) {
			ProgressAnimations();
			AI();
			Physics();
			CollisionChecking();
			CommitDestructions();
			//UserCode();
		}
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
		//std::cout << "CPU time was:" << averageFrameTimeMilliseconds << std::endl;
	}
}
