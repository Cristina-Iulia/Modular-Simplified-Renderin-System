#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER
#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../SwapChain/SwapChain.h"
#include "../../CoreSystems/Window/Window.h"
#include "../../DeviceContext.h"
#include "spdlog/spdlog.h"

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
	DeviceContext* devContext;

};

#endif