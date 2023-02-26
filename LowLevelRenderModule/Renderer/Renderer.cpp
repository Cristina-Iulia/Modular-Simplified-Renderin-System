#include "Renderer.h"
#include <stdexcept>

static Renderer* rdSingleton = nullptr;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::init()
{
	sglHwnd = Window::getInstance();
	if (sglHwnd == nullptr)
	{
		spdlog::critical("Bad instance: Window -> nullptr");
	}


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
	else {

		RECT rc = sglHwnd->getWindowRect();
		sglSwapChain->init(this->sglHwnd->getWindowDesc(), rc.right-rc.left, rc.bottom-rc.top);
	}

	devContext = new DeviceContext();
	devContext->init();


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




