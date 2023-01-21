#pragma once
#include "../../CoreSystems/DeviceManager/DeviceManager.h"


class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	void init();
	void release();

	static SwapChain* getInstance();
	static SwapChain* swapSingleton;
};

