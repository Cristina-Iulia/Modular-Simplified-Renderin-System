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

	devContext = new DeviceContext();
	devContext->init();

	renderTarget = sglSwapChain->getRenderTarget();
	depthStencil = sglSwapChain->getDepthStencil();

	congigureResterizer();

	return true;
}

bool Renderer::release()
{
	m_blob->Release();
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

void Renderer::compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	//if (!(m_blob == nullptr))
		//m_blob->Release();
	HRESULT result = ::D3DCompileFromFile(file, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &m_blob, &error_blob);

	if (FAILED(result))
	{
		spdlog::critical("VertexShader compilation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
		if (error_blob)
			error_blob->Release();
		exit(1);
	}

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void Renderer::compilePixelShader(const wchar_t * file, const char * entryPointName, void ** shaderByteCode, size_t * byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	if (m_blob)
		m_blob->Release();
	HRESULT result = ::D3DCompileFromFile(file, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &m_blob, &error_blob);

	if (FAILED(result))
	{
		spdlog::critical("PixelShader compilation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
		if (error_blob)
			error_blob->Release();
		exit(1);
	}

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void Renderer::releaseCompiledShader()
{
	if (m_blob)
		m_blob->Release();
}

void Renderer::setResterizerState(Cull_type type)
{
	if (type == CULL_FRONT)
	{
		devContext->setRSState(front_colling);
	}
	else if (type == CULL_BACK)
	{
		devContext->setRSState(back_colling);
	}
	else
	{
		spdlog::critical("Unkown culling type");
	}
}

void Renderer::createVertexShader(void* shaderByteCode, size_t byteCodeSize)
{
	vertexShader = std::make_shared <VertexShader>();
	vertexShader->init(shaderByteCode, byteCodeSize);
}

void Renderer::createVertexMeshShader(void * shaderByteCode, size_t byteCodeSize)
{
	vertexMeshShader = std::make_shared <VertexShader>();
	vertexMeshShader->init(shaderByteCode, byteCodeSize);
}


void Renderer::createPixelShader(void* shaderByteCode, size_t byteCodeSize)
{
	pixelShader = std::make_shared <PixelShader>();
	pixelShader->init(shaderByteCode, byteCodeSize);
}

void Renderer::createEnvPixelShader(void* shaderByteCode, size_t byteCodeSize)
{
	envPixelShader = std::make_shared <PixelShader>();
	envPixelShader->init(shaderByteCode, byteCodeSize);
}