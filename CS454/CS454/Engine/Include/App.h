#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <ctime>

namespace app {
	class Game { // app::Game namespace, the mother application
		public:
			using Action = std::function<void(void)>;
			using Pred = std::function<bool(void)>;
			clock_t deltaTime = 0;
			unsigned int frames = 0;
			double  frameRate = 30;
			double  averageFrameTimeMilliseconds = 33.333;
		private:
			Action render, anim, input, ai, physics, destruct, collisions, user, pauseResume,inputexec,input_update;
			Pred done;
			bool isPaused = false;
			uint64_t pauseTime = 0;
			void Invoke(const Action& f) { if (f) f(); }
			
		public:
			void SetOnPauseResume (const Action& f) 
			{ pauseResume = f;}
			void Pause (uint64_t t)
			{ isPaused = true; pauseTime = t; Invoke(pauseResume); }
			void Resume (void)
			{ isPaused = false; Invoke(pauseResume); pauseTime = 0; }
			bool IsPaused (void) const
			{ return isPaused; }
			uint64_t GetPauseTime (void) const
			{ return pauseTime; }
			void set_pause(bool val) { isPaused = val; }
			void SetRender(const Action& f) { render = f; }
			void SetInput(const Action& f) { input = f; }
			void SetInputExec(const Action& f) { inputexec = f; }
			void SetInputUpdate(const Action& f) { input_update = f; }
			void SetDone(const Pred& f) { done = f; }
			void SetAnim(const Action& f) { anim = f;  }
			void Set_Physics(const Action& f) { physics = f; }
            void SetCollisionChecking(const Action& f) { collisions = f; }
			void Set_AI(const Action& f) { ai = f; }
			void Set_destr(const Action& f) { destruct = f; }
			// rest of setters are similary defined
			void Render(void){ Invoke(render); }
			void ProgressAnimations(void) { Invoke(anim); }
			void Input(void) { Invoke(input); }
			void AI(void) { Invoke(ai); }
			void Physics(void) { Invoke(physics); }
			void CollisionChecking(void) { Invoke(collisions); }
			void CommitDestructions(void) { Invoke(destruct); }
			void UserCode(void) { Invoke(user); }
			bool IsFinished(void) const { return !done(); }
			void MainLoop(void);
			void MainLoopIteration(void);
			double clockToMilliseconds(clock_t ticks){ return (ticks / (double)CLOCKS_PER_SEC) * 1000.0; }
	};

	class App {
		protected:
			Game game;
		
		public:
			virtual void Initialise(void) = 0;
			virtual void Load(void) = 0;
			virtual void Run(void) { game.MainLoop(); }
			virtual void RunIteration(void) { game.MainLoopIteration(); }

			Game& GetGame(void) { return game; }
			const Game& GetGame(void) const { return game; }
			virtual void Clear(void) = 0;
			void Main(void) {
				Initialise();
				//Load();
				//Run();
				//Clear();
			}
	};
}