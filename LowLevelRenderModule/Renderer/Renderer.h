#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER
#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../SwapChain/SwapChain.h"
#include <Windows.h>
#include "../../DeviceContext.h"
#include "spdlog/spdlog.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	bool init(HWND m_hwnd, RECT rc);
	bool release();
	static Renderer* getInstance();

	void clearRenderTarget(float red, float green, float blue, float alpha);
	void present(bool vsync);
	void createVertexBuffer();

	VertexBuffer* vertexBuffer;
	DeviceContext* devContext;
private:
	DeviceManager* sglDeviceManager;
	SwapChain* sglSwapChain;
	ID3D11RenderTargetView* renderTarget;


};

#endif