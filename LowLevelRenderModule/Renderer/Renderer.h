#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER

#include <Windows.h>
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

#include "../DeviceContext/DeviceContext.h"
#include "../Resources.h"

enum Cull_type
{
	CULL_FRONT,
	CULL_BACK
};

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
	void createEnvPixelShader(void* shaderByteCode, size_t byteCodeSize);
	void createVertexBuffer();
	ConstantBufferPtr createConstantBuffer();
	void createIndexBuffer();


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(float red, float green, float blue, float alpha);
	void present(bool vsync);

	void compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void compilePixelShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();

	void setResterizerState(Cull_type type);

	// RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES
	VertexBufferPtr vertexBuffer = nullptr;
	ConstantBufferPtr constantBuffer = nullptr;
	ConstantBufferPtr envConstantBuffer = nullptr;
	VertexShaderPtr vertexShader = nullptr;
	VertexShaderPtr vertexMeshShader = nullptr;
	PixelShaderPtr pixelShader = nullptr;
	PixelShaderPtr envPixelShader = nullptr;
	IndexBufferPtr indexBuffer = nullptr;

	DeviceContext* devContext;

private:
	~Renderer();

	void congigureResterizer();
	ID3D11RasterizerState* front_colling = nullptr;
	ID3D11RasterizerState* back_colling = nullptr;

	SwapChain* sglSwapChain = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;
	ID3D11DepthStencilView* depthStencil = nullptr;

	ID3DBlob* m_blob = nullptr;

};

#endif