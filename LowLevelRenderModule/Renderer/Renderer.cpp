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
		std::runtime_error("Bad instance: Window -> nullptr");
	}


	sglDeviceManager = DeviceManager::getInstance();
	if (sglDeviceManager == nullptr)
	{
		std::runtime_error("Bad instance: DeviceManager -> nullptr");
	}


	sglSwapChain = SwapChain::getInstance();
	if (sglSwapChain == nullptr)
	{
		std::runtime_error("Bad instance: SwapChain -> nullptr");
	}
	else {

		RECT rc = sglHwnd->getWindowRect();
		sglSwapChain->init(this->sglHwnd->getWindowDesc(), rc.right-rc.left, rc.bottom-rc.top);
	}


	return true;
}

bool Renderer::release()
{
	sglSwapChain->release();
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




