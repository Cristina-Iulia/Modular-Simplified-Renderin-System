#pragma once

// Imports
#include "../Window/Window.h"
#include "../../LowLevelRenderModule/Renderer/Renderer.h"
#include "../DeviceManager/DeviceManager.h"


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
	DeviceManager* sglDeviceManager;
	Window* sglWindow;
	Renderer* sglRenderer;
	
};

