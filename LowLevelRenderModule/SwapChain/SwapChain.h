#pragma once
#ifndef  SWAPCHAIN_MECHANISM
#define SWAPCHAIN_MECHANISM

#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "spdlog/spdlog.h"


class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	void init(HWND hwnd, UINT width, UINT height);
	void release();

	static SwapChain* getInstance();


private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
};

#endif