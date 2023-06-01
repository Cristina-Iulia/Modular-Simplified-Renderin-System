#pragma once
#ifndef  DEV_CONTEXT
#define DEV_CONTEXT

#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

#include "../Resources.h"
#include "../../ResourceManagerModule/Include.h"

class DeviceContext
{
public:
	void init();
	void release();

	DeviceContext();

	// SETER --- SETER --- SETER --- SETER --- SETER
	void setVertexBuffer(const VertexBufferPtr& vertex_buffer);
	void setIndexBuffer(const IndexBufferPtr& index_buffer);
	void setVertexShader(const VertexShaderPtr& vertex_shader);
	void setViewportSize(UINT width, UINT height);
	void setPixelShader(const PixelShaderPtr& pixel_shader);
	void setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& constant_buffer);
	void setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& constant_buffer);
	void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr& texture);
	void setTexture(const PixelShaderPtr& pixel_shader, const TexturePtr& texture);


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(ID3D11RenderTargetView* target, float red, float green, float blue, float alpha);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);


private:
	~DeviceContext();

	ID3D11DeviceContext* m_dev_Context = nullptr;


};

#endif
