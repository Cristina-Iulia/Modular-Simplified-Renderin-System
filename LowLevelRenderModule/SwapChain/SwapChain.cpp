#include "SwapChain.h"
#include <stdexcept>

static SwapChain* swapSingleton = nullptr;

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = DeviceManager::getDevice();
	DXGI_SWAP_CHAIN_DESC desc; //declare swap chain descriptor
	desc.BufferCount = 1; //set the number of backbuffers to be used to one
	desc.BufferDesc.Width = width; //set width of backbuffer
	desc.BufferDesc.Height = height; //set height of backbuffer
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //allaow 8 bit unsigned int per channel of color buffer (maybe change later to DXGI_FORMAT_R16G16B16A16_FLOAT)
	desc.BufferDesc.RefreshRate.Numerator = 60; //set refrash rate (must be made customisable later)
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1; //samples per pixel
	desc.SampleDesc.Quality = 0;
	//desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.Windowed = TRUE;

	HRESULT result = DeviceManager::getFactory()->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(result))
	{
		std::runtime_error("SwapChain creation UNSUCCESSFUL");
	}

}

void SwapChain::release()
{
	m_swap_chain->Release();
}

SwapChain * SwapChain::getInstance()
{
	if (swapSingleton == nullptr)
	{
		swapSingleton = new SwapChain();
		return swapSingleton;
	}
	else
	{
		return swapSingleton;
	}

	return nullptr;
}
