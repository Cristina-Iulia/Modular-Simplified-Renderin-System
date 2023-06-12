#pragma once
#ifndef  DEVICE_CONTEXT
#define  DEVICE_CONTEXT

#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"
#include "../../ResourceManagerModule/Include.h"

#include "../../MemoryBuffers/MemoryBufferLib.h"
#include "../Shaders/ShadersLib.h"


typedef std::shared_ptr<Texture> TexturePtr;

class DeviceContext
{
public:
	void init(ID3D11RasterizerState* front_colling, ID3D11RasterizerState* back_colling);
	void release();

	DeviceContext();

	// SETER --- SETER --- SETER --- SETER --- SETER
	void setVertexBuffer(VertexBufferPtr vertex_buffer);
	void setIndexBuffer(IndexBufferPtr index_buffer);
	void setVertexShader(VertexShaderPtr vertex_shader);
	void setViewportSize(UINT width, UINT height);
	void setPixelShader(PixelShaderPtr pixel_shader);
	void setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr constant_buffer);
	void setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr constant_buffer);
	void setTexture(VertexShaderPtr vertex_shader, TexturePtr* texture, unsigned int tex_nr);
	void setTexture(PixelShaderPtr pixel_shader, TexturePtr* texture, unsigned int tex_nr);
	void setMaterial(const MaterialPtr& material);
	void setRSState(Cull_type type);


	// ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS --- ACTIONS
	void clearRenderTarget(ID3D11RenderTargetView* target, ID3D11DepthStencilView* depth_view, float red, float green, float blue, float alpha);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);


private:
	~DeviceContext();

	ID3D11DeviceContext* m_dev_Context = nullptr;
	ID3D11RasterizerState* front_colling = nullptr;
	ID3D11RasterizerState* back_colling = nullptr;


};

#endif
