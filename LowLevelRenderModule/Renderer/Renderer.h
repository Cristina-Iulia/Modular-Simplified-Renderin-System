#pragma once
#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../SwapChain/SwapChain.h"
#include "../../CoreSystems/Window/Window.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	bool init();
	bool release();
	static Renderer* getInstance();


private:
	DeviceManager* sglDeviceManager;
	SwapChain* sglSwapChain;
	Window* sglHwnd;

};

