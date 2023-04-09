#include "Renderer.h"
#include <stdexcept>

static Renderer* rdSingleton = nullptr;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::init(HWND m_hwnd, RECT rc)
{

	sglDeviceManager = DeviceManager::getInstance();
	if (sglDeviceManager == nullptr)
	{
		spdlog::critical("Bad instance: DeviceManager -> nullptr");
	}


	sglSwapChain = SwapChain::getInstance();
	if (sglSwapChain == nullptr)
	{
		spdlog::critical("Bad instance: SwapChain -> nullptr");
	}
	else 
	{
		sglSwapChain->init(m_hwnd, rc.right-rc.left, rc.bottom-rc.top);
	}

	devContext = new DeviceContext();
	devContext->init();

	renderTarget = sglSwapChain->getRenderTarget();

	return true;
}

bool Renderer::release()
{
	sglSwapChain->release();
	devContext->release();
	return true;
}

Renderer * Renderer::getInstance()
{
	if (rdSingleton == nullptr)
	{
		rdSingleton = new Renderer();
		return rdSingleton;
	}
	else
	{
		return rdSingleton;
	}

	return nullptr;
}

void Renderer::clearRenderTarget( float red, float green, float blue, float alpha)
{
	this->devContext->clearRenderTarget(this->renderTarget, red, green, blue, alpha);
}

void Renderer::present(bool vsync)
{
	sglSwapChain->present(vsync);
}


