#include "../Include/ZeldaApp.h"
#include "SDL.h"
#include "SDL_Image.h"

SDL_Renderer* myrenderer;

std::vector<std::vector<std::string>> content;
SDL_Surface* tempSurface;

float CameraPosX = 0.0;
float CameraPosY = 0.0;

int MouseX;
int MouseY;

void MapLoader() {
	SDL_Texture* tex;
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	tex = SDL_CreateTextureFromSurface(myrenderer, tempSurface);

	for (int i = 0; i < content.size(); i++) {
		for (int j = 0; j < content[i].size(); j++) {
			int id = stoi(content[i][j]);

			srcrect.x = (id % 12) * 16;
			srcrect.y = (id / 12) * 16;
			srcrect.h = srcrect.w = 16;

			dstrect.x = (j + CameraPosX) * 48;
			dstrect.y = (i + CameraPosY) * 48;
			dstrect.h = dstrect.w = 48;

			SDL_RenderCopy(myrenderer, tex, &srcrect, &dstrect);
		}
	}

}

void myRender() {
	SDL_RenderClear(myrenderer);
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type) {

	/*case SDL_MOUSEBUTTONDOWN:
		case SDL_BUTTON_LEFT:
			std::cout << "PEOS";
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&MouseX, &MouseY);
		std::cout << MouseX << ":" << MouseY << std::endl;
		break;*/
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				CameraPosY = CameraPosY - 0.1;
				break;
			case SDLK_UP:
				CameraPosY = CameraPosY + 0.1;
				break;
			case SDLK_LEFT:
				CameraPosX = CameraPosX + 0.1;
				break;
			case SDLK_RIGHT:
				CameraPosX = CameraPosX - 0.1;
				break;
			default:
				break;
		}
		break;
	}

	MapLoader();

	//your stuff to render would typically go here.
	SDL_RenderPresent(myrenderer);
}


void ZeldaApp::Initialise() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		SDL_Window* window = SDL_CreateWindow("ZeldaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		if (window) std::cout << "Window created!" << std::endl;


		myrenderer = SDL_CreateRenderer(window, -1, 0);
		if (myrenderer)
		{
			SDL_SetRenderDrawColor(myrenderer, 255, 255, 255, 255);

			editor.parse("map.csv");
			tempSurface = IMG_Load("overworld_tileset_grass.png");
			content = editor.content;

			std::cout << "Renderer created!" << std::endl;
		}
	}

	game.SetRender(myRender);

	
	editor = MapEditor::Editor();
	//std::string path = ;
	editor.parse("map.csv");
	editor.print();

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