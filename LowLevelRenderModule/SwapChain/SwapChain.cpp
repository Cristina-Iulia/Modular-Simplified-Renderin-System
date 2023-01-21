#include "SwapChain.h"

SwapChain* SwapChain::swapSingleton = nullptr;

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::init()
{
	ID3D11Device* device = DeviceManager::getDevice();
	DXGI_SWAP_CHAIN_DESC desc; //declare swap chain descriptor
	desc.BufferCount = 1; //set the number of backbuffers to be used to one
}

void SwapChain::release()
{
}

SwapChain * SwapChain::getInstance()
{
	if (SwapChain::swapSingleton == nullptr)
	{
		SwapChain::swapSingleton = new SwapChain;
		return swapSingleton;
	}
	else
	{
		return swapSingleton;
	}

	return nullptr;
}
