#pragma once

// Imports
#include "../Window/Window.h"
#include "../DeviceManager/DeviceManager.h"
#include "../../LowLevelRenderModule/Renderer/Renderer.h"


class Controller
{
public:
	Controller();
	~Controller();
	void Startup();
	void ShutDown();
	static Controller* getInstance();


protected:

	void init();
	void release();
	Window* sglWindow;
	DeviceManager* sglDeviceManager;
	Renderer* sglRenderer;
	
};

