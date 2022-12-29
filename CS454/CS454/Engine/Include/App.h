#pragma once
#include <iostream>
#include <functional>
#include <vector>


namespace app {
	class Game { // app::Game namespace, the mother application
		public:
			using Action = std::function<void(void)>;
			using Pred = std::function<bool(void)>;
		private:
			Action render, anim, input, ai, physics, destruct, collisions, user;
			Pred done;
			void Invoke(const Action& f) { if (f) f(); }
			
		public:
			void SetRender(const Action& f) { render = f; }
			// rest of setters are similary defined
			void Render(void){ Invoke(render); }
			//void ProgressAnimations(void) { Invoke(anim); }
			//void Input(void) { Invoke(input); }
			//void AI(void) { Invoke(ai); }
			//void Physics(void) { Invoke(physics); }
			//void CollisionChecking(void) { Invoke(collisions); }
			//void CommitDestructions(void) { Invoke(destruct); }
			//void UserCode(void) { Invoke(user); }
			bool IsFinished(void) const { return false; }
			void MainLoop(void);
			void MainLoopIteration(void);
			//SDL_Renderer* myrenderer;
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