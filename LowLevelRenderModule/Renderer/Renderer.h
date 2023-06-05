#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER

#include <Windows.h>
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

#include "../DeviceContext/DeviceContext.h"
#include "../Resources.h"



class Renderer
{
public:
	Renderer();

	bool init(HWND m_hwnd, RECT rc);
	bool release();

	static Renderer* getInstance();

	// CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES
	void createVertexShader(void* shaderByteCode, size_t byteCodeSize);
	void createVertexMeshShader(void* shaderByteCode, size_t byteCodeSize);
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
	VertexBufferPtr vertexBuffer = nullptr;
	ConstantBufferPtr constantBuffer = nullptr;
	VertexShaderPtr vertexShader = nullptr;
	VertexShaderPtr vertexMeshShader = nullptr;
	PixelShaderPtr pixelShader = nullptr;
	IndexBufferPtr indexBuffer = nullptr;

	DeviceContext* devContext;

	//unsigned char m_mesh_layout_byte_code[1024];
	//size_t m_mesh_layout_size = 0;

	//void getVertexMeshLayoutShaderByteCodeAndSize(void ** byte_code, size_t* size);

private:
	~Renderer();

	SwapChain* sglSwapChain = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;

	ID3DBlob* m_blob = nullptr;

};

#endif