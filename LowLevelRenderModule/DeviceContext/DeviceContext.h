#pragma once
#ifndef  DEV_CONTEXT
#define DEV_CONTEXT

#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../SwapChain/SwapChain.h"
#include "../MemoryBuffers/VertexBuffer/VertexBuffer.h"
#include "../Shaders/VertexShader/VertexShader.h"
#include "../Shaders/PixelShader/PixelShader.h"
#include "../MemoryBuffers/ConstantBuffer/ConstantBuffer.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

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
	void setPixelShader(PixelShader* pixel_shader);
	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer);


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(ID3D11RenderTargetView* target, float red, float green, float blue, float alpha);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);


private:
	~DeviceContext();

	ID3D11DeviceContext* m_dev_Context = nullptr;


};

#endif
