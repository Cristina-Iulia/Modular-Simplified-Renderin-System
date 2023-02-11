#pragma once
#include "../../CoreSystems/DeviceManager/DeviceManager.h"


class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	void init(HWND hwnd, UINT width, UINT height);
	void release();

	static SwapChain* getInstance();


private:
	IDXGISwapChain* m_swap_chain = nullptr;
};

