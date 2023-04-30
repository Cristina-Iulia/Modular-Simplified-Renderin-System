#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER

#include "../SwapChain/SwapChain.h"
#include <Windows.h>
#include "../../DeviceContext.h"
#include "spdlog/spdlog.h"

class Renderer
{
public:
	Renderer();

	bool init(HWND m_hwnd, RECT rc);
	bool release();

	static Renderer* getInstance();

	// CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES
	void createVertexShader(void* shaderByteCode, size_t byteCodeSize);
	void createPixelShader();
	void createVertexBuffer();


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(float red, float green, float blue, float alpha);
	void present(bool vsync);

	void compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();

	// RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES
	VertexBuffer* vertexBuffer = nullptr;
	VertexShader* vertexShader = nullptr;

	DeviceContext* devContext = nullptr;
	ID3D11PixelShader* m_ps = nullptr;


private:
	~Renderer();

	SwapChain* sglSwapChain = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;

};

#endif