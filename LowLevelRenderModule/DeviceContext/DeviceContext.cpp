#include "DeviceContext.h"


void DeviceContext::init()
{
	m_dev_Context = DeviceManager::getDeviceContext();
}

void DeviceContext::release()
{
	delete this;
}

DeviceContext::DeviceContext()
{
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::clearRenderTarget(ID3D11RenderTargetView* target, float red, float green, float blue, float alpha)
{
	float color_channel[] = { red, green, blue, alpha };
	m_dev_Context->ClearRenderTargetView(target, color_channel);
	m_dev_Context->OMSetRenderTargets(1, &target, NULL);
}

void DeviceContext::setVertexBuffer(VertexBufferPtr vertex_buffer)
{
	UINT stried = vertex_buffer->sizeOfVertex;
	UINT offset = 0;
	m_dev_Context->IASetVertexBuffers(0, 1, &vertex_buffer->buffer, &stried, &offset);
	m_dev_Context->IASetInputLayout(vertex_buffer->inputLayout);
}

void DeviceContext::setIndexBuffer(IndexBufferPtr index_buffer)
{
	m_dev_Context->IASetIndexBuffer(index_buffer->buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setVertexShader(VertexShaderPtr vertex_shader)
{
	m_dev_Context->VSSetShader(vertex_shader->getShader(), nullptr, 0);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	m_dev_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_dev_Context->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndex)
{
	m_dev_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_dev_Context->DrawIndexed(indexCount, startIndex, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	m_dev_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_dev_Context->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	UINT numberOfViewports = 1;
	m_dev_Context->RSSetViewports(numberOfViewports, &vp);
}


void DeviceContext::setPixelShader(PixelShaderPtr pixel_shader)
{
	m_dev_Context->PSSetShader(pixel_shader->getShader(), nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr constant_buffer)
{
	m_dev_Context->VSSetConstantBuffers(0,1, &constant_buffer->constBuffer);
}

void DeviceContext::setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr constant_buffer)
{
	m_dev_Context->PSSetConstantBuffers(0, 1, &constant_buffer->constBuffer);
}

void DeviceContext::setTexture(VertexShaderPtr vertex_shader, TexturePtr texture)
{
	m_dev_Context->VSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void DeviceContext::setTexture(PixelShaderPtr pixel_shader, TexturePtr texture)
{
	m_dev_Context->PSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

