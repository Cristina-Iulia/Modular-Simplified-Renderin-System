#pragma once
#ifndef  DEV_CONTEXT
#define DEV_CONTEXT

#include <d3d11.h>
#include "CoreSystems/DeviceManager/DeviceManager.h"
#include "LowLevelRenderModule/SwapChain/SwapChain.h"

class DeviceContext
{
public:
	void init();
	void release();

	DeviceContext();
	~DeviceContext();

	void clearRenderTarget(ID3D11RenderTargetView* target, float red, float green, float blue, float alpha);

private:
	ID3D11DeviceContext* m_dev_Context;

};

#endif
