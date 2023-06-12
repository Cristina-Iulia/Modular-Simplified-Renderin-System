#pragma once
#ifndef  RENDERER
#define RENDERER

#include <Windows.h>
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

#include "../DeviceContext/DeviceContext.h"
#include "../../MemoryBuffers/MemoryBufferLib.h"
#include "../Shaders/ShaderManager/ShaderManager.h"
#include "../SwapChain/SwapChain.h"

class Renderer
{
public:
	Renderer();

	bool init(HWND m_hwnd, RECT rc);
	bool release();

	static Renderer* getInstance();

	// CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES --- CREATE RESOURCES
	void createVertexBuffer();
	ConstantBufferPtr createConstantBuffer();
	void createIndexBuffer();


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(float red, float green, float blue, float alpha);
	void present(bool vsync);

	// RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES --- RESOURCES
	VertexBufferPtr vertexBuffer = nullptr;
	IndexBufferPtr indexBuffer = nullptr;

	DeviceContext* devContext;
	ShaderManager* shaderManager;

private:
	~Renderer();

	void congigureResterizer();
	ID3D11RasterizerState* front_colling = nullptr;
	ID3D11RasterizerState* back_colling = nullptr;

	SwapChain* sglSwapChain = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;
	ID3D11DepthStencilView* depthStencil = nullptr;

};

#endif