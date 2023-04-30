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
	vertexBuffer->release();
	vertexShader->release();
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

void Renderer::createVertexBuffer()
{
	vertexBuffer =  new VertexBuffer();
}

void Renderer::compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT result = ::D3DCompileFromFile(file, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &m_blob, &error_blob);

	if (FAILED(result))
	{
		spdlog::critical("VertexShader compilation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
		exit(1);
	}

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void Renderer::compilePixelShader(const wchar_t * file, const char * entryPointName, void ** shaderByteCode, size_t * byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT result = ::D3DCompileFromFile(file, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &m_blob, &error_blob);

	if (FAILED(result))
	{
		spdlog::critical("PixelShader compilation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
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

void Renderer::createVertexShader(void* shaderByteCode, size_t byteCodeSize)
{
	vertexShader = new VertexShader();
	vertexShader->init(shaderByteCode, byteCodeSize);
}


void Renderer::createPixelShader(void* shaderByteCode, size_t byteCodeSize)
{
	pixelShader = new PixelShader();
	pixelShader->init(shaderByteCode, byteCodeSize);
}
