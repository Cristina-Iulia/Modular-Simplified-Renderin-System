#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER

#include <Windows.h>
#include "../SwapChain/SwapChain.h"
#include "../DeviceContext/DeviceContext.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"


class Renderer
{
public:
	Renderer();

	bool init(HWND m_hwnd, RECT rc);
	bool release();

	static Renderer* getInstance();

	// CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES
	void createVertexShader(void* shaderByteCode, size_t byteCodeSize);
	void createPixelShader(void* shaderByteCode, size_t byteCodeSize);
	void createVertexBuffer();
	void createConstantBuffer();
	void createIndexBuffer();


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(float red, float green, float blue, float alpha);
	void present(bool vsync);

	void compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void compilePixelShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();

	// RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES
	VertexBuffer* vertexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	IndexBuffer* indexBuffer = nullptr;

	DeviceContext* devContext = nullptr;


private:
	~Renderer();

	SwapChain* sglSwapChain = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;

	ID3DBlob* m_blob = nullptr;

};

#endif