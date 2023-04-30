#pragma once
#ifndef  DEV_CONTEXT
#define DEV_CONTEXT

#include <d3d11.h>
#include <d3dcompiler.h>
#include "CoreSystems/DeviceManager/DeviceManager.h"
#include "LowLevelRenderModule/SwapChain/SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "spdlog/spdlog.h"

class DeviceContext
{
public:
	void init();
	void release();

	DeviceContext();
	~DeviceContext();

	void clearRenderTarget(ID3D11RenderTargetView* target, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setVertexShader(VertexShader* vertex_shader);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void setViewportSize(UINT width, UINT height);

	void createShaders();
	void setShaders();

private:
	ID3D11DeviceContext* m_dev_Context = nullptr;
	SwapChain* swapChain = nullptr;
	ID3D11Device* m_d3dDevice = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

};

#endif
