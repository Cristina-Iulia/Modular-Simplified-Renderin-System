#pragma once

// Imports
#include "../Window/Window.h"
#include "../../Renderer.h"


class Controller
{
public:
	Controller();
	~Controller();
	void Startup();
	void ShutDown();
	static Controller* crtModule;
	static Controller* getInstance();


protected:

	void init();
	void release();
	Window* sglWindow;
	Renderer* sglRenderer;
	
};

