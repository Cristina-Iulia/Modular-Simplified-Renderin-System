#pragma once
#ifndef  DEV_CONTEXT
#define DEV_CONTEXT

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

	// SETER --- SETER --- SETER --- SETER --- SETER
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setVertexShader(VertexShader* vertex_shader);
	void setViewportSize(UINT width, UINT height);
	void setPixelShaders(ID3D11PixelShader* m_ps);


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(ID3D11RenderTargetView* target, float red, float green, float blue, float alpha);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);


private:
	~DeviceContext();

	ID3D11DeviceContext* m_dev_Context = nullptr;


};

#endif
