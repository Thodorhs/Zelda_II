#pragma once
#include "App.h"
#include "Editor.h"

class ZeldaApp :app::App {
	private:
		 MapEditor::Editor editor;
	public:
		
		void Initialise(void);
		void Load(void);
		void Clear(void);
		void Run(void);
		void RunIteration(void);
};