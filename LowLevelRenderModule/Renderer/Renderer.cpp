#include "Renderer.h"
#include <stdexcept>

static Renderer* rdSingleton = nullptr;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::congigureResterizer()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;

	DeviceManager::getDevice()->CreateRasterizerState(&desc, &front_colling);


	desc.CullMode = D3D11_CULL_BACK;
	DeviceManager::getDevice()->CreateRasterizerState(&desc, &back_colling);
}

bool Renderer::init(HWND m_hwnd, RECT rc)
{
	sglSwapChain = SwapChain::getInstance();
	if (sglSwapChain == nullptr)
	{
		spdlog::critical("Bad instance: SwapChain -> nullptr");
	}
	else 
	{
		sglSwapChain->init(m_hwnd, rc.right-rc.left, rc.bottom-rc.top);
	}

	congigureResterizer();

	devContext = new DeviceContext();
	devContext->init(front_colling, back_colling);

	renderTarget = sglSwapChain->getRenderTarget();
	depthStencil = sglSwapChain->getDepthStencil();

	

	shaderManager = ShaderManager::getInstance();

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
	this->devContext->clearRenderTarget(this->renderTarget, this->depthStencil, red, green, blue, alpha);
}

void Renderer::present(bool vsync)
{
	sglSwapChain->present(vsync);
}

void Renderer::createVertexBuffer()
{
	vertexBuffer = std::make_shared<VertexBuffer>();
}

ConstantBufferPtr Renderer::createConstantBuffer()
{
	ConstantBufferPtr buffer;
	buffer = std::make_shared <ConstantBuffer>();
	return buffer;
}

void Renderer::createIndexBuffer()
{
	indexBuffer = std::make_shared <IndexBuffer>();
}