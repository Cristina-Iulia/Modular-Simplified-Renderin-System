#pragma once
#ifndef  SWAPCHAIN_MECHANISM
#define SWAPCHAIN_MECHANISM

#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"



class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	void init(HWND hwnd, UINT width, UINT height);
	void release();

	static SwapChain* getInstance();
	ID3D11RenderTargetView* getRenderTarget();
	void present(bool vsync);

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
};

#endif