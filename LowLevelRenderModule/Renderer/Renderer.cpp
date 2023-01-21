#include "Renderer.h"

Renderer* Renderer::rdSingleton = nullptr;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::init()
{
	sglDeviceManager = DeviceManager::getInstance();

	if (sglDeviceManager == nullptr)
	{

	}

	return true;
}

bool Renderer::release()
{
	sglDeviceManager->relese();

	return true;
}

Renderer * Renderer::getInstance()
{
	if (Renderer::rdSingleton == nullptr)
	{
		Renderer::rdSingleton = new Renderer;
		return rdSingleton;
	}
	else
	{
		return rdSingleton;
	}

	return nullptr;
}




