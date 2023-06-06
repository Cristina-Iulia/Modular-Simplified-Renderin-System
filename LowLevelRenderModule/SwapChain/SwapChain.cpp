#include "SwapChain.h"


static SwapChain* swapSingleton = nullptr;

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	spdlog::info("__Initializing SwapChain Entity__ : STARTED");
	ID3D11Device* device = DeviceManager::getDevice();
	
	if (device == nullptr)
	{
		spdlog::critical("DEVICE retrieval returned NULLPTR");
	}
	DXGI_SWAP_CHAIN_DESC desc = {}; //declare swap chain descriptor
	desc.BufferCount = 2; //set the number of backbuffers to be used to one
	desc.BufferDesc.Width = width; //set width of backbuffer
	desc.BufferDesc.Height = height; //set height of backbuffer
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //allaow 8 bit unsigned int per channel of color buffer (maybe change later to DXGI_FORMAT_R16G16B16A16_FLOAT)
	desc.BufferDesc.RefreshRate.Numerator = 60; //set refrash rate (must be made customisable later)
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; //does not support multisampling
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1; //samples per pixel
	desc.SampleDesc.Quality = 0;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.Windowed = TRUE;

	spdlog::info("SwapChain internal startup parameters set");
	auto factory = DeviceManager::getFactory();
	HRESULT result = factory->CreateSwapChain(reinterpret_cast<IUnknown*>(device), &desc, &m_swap_chain);
	if (FAILED(result))
	{
		spdlog::critical("SwapChain creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
		return;
	}
	else
	{
		if (m_swap_chain != nullptr)
		{
			spdlog::info("SwapChain creation SUCCESSFUL");
		}
		else
		{
			spdlog::critical("SwapChain creation UNSUCCESSFUL");
		}
	}

	// get the back buffer of the swap chain
	ID3D11Texture2D* buffer = nullptr;
	HRESULT result_ = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer));

	if (FAILED(result_))
	{
		spdlog::critical("BackBuffer retival UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result_));
		return;
	}
	else
	{
		spdlog::info("BackBuffer retival SUCCESSFUL");
	}

	// create a render target using the back buffer retrieved earlier
	result = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(result))
	{
		spdlog::critical("Render Target View creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}
	else
	{
		spdlog::info("Render Target View creation SUCCESSFUL");
	}

	D3D11_TEXTURE2D_DESC textdesc = {};
	textdesc.Width = width;
	textdesc.Height = height;
	textdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textdesc.Usage = D3D11_USAGE_DEFAULT;
	textdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textdesc.MipLevels = 1;
	textdesc.SampleDesc.Count = 1;
	textdesc.SampleDesc.Quality = 0;
	textdesc.MiscFlags = 0;
	textdesc.ArraySize = 1;
	textdesc.CPUAccessFlags = 0;

	result = device->CreateTexture2D(&textdesc, nullptr, &buffer);

	if (FAILED(result))
	{
		spdlog::critical("Depth texture creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}
	else
	{
		spdlog::info("Depth texture creation SUCCESSFUL");
	}

	result = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	buffer->Release();

	if (FAILED(result))
	{
		spdlog::critical("Depth stencile view creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}
	else
	{
		spdlog::info("Depth stencile view creation SUCCESSFUL");
	}


	spdlog::info("__Initializing SwapChain Entity__ : FINISHED");
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

ID3D11RenderTargetView * SwapChain::getRenderTarget()
{
	if (m_rtv == nullptr)
	{
		spdlog::critical("ERROR AT : SwapChain::RENDER_TARGET retrieval");
	}
	else
	{
		spdlog::info("Retrieve SwapChain::RENDER_TARGET");
		return m_rtv;
	}

	spdlog::critical("ERROR AT : SwapChain::RENDER_TARGET retrieval");
	return nullptr;
}

ID3D11DepthStencilView * SwapChain::getDepthStencil()
{
	if (m_dsv == nullptr)
	{
		spdlog::critical("ERROR AT : SwapChain::DEPTH_STENCIL retrieval");
	}
	else
	{
		spdlog::info("Retrieve SwapChain::DEPTH_STENCIL");
		return m_dsv;
	}

	spdlog::critical("ERROR AT : SwapChain::DEPTH_STENCIL retrieval");
	return nullptr;
}

void SwapChain::present(bool vsync)
{
	HRESULT res = m_swap_chain->Present(vsync, NULL);

	if (FAILED(res))
	{
		spdlog::critical("Presentation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(res));
	}
}
