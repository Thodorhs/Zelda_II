#include "../Include/ZeldaApp.h"
#include "SDL.h"
#include "SDL_image.h"

void ZeldaApp::Initialise() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		SDL_Window* window = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (window) std::cout << "Window created!" << std::endl;

		SDL_Renderer* myrenderer = SDL_CreateRenderer(window, -1, 0);
		if (myrenderer)
		{
			SDL_SetRenderDrawColor(myrenderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
	}
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load("overworld_tileset_grass.png");
	//std::cout << "hello world" << std::endl;
	//game.SetRender(myRender);

}

void ZeldaApp::Load() {

}

void ZeldaApp::Run() {
	game.MainLoop();
}

void ZeldaApp::RunIteration() {
	game.MainLoopIteration();
}

void ZeldaApp::Clear() {

}