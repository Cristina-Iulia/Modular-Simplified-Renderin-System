#include "DeviceContext.h"


void DeviceContext::init()
{
	this->m_dev_Context = DeviceManager::getDeviceContext();
	this->swapChain = SwapChain::getInstance();
	this->m_d3dDevice = DeviceManager::getDevice();
}

void DeviceContext::release()
{
	this->m_dev_Context->Release();
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
	this->m_dev_Context->ClearRenderTargetView(target, color_channel);
	this->m_dev_Context->OMSetRenderTargets(1, &target, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer * vertex_buffer)
{
	UINT stried = vertex_buffer->sizeOfVertex;
	UINT offset = 0;
	this->m_dev_Context->IASetVertexBuffers(0, 1, &vertex_buffer->buffer, &stried, &offset);
	this->m_dev_Context->IASetInputLayout(vertex_buffer->inputLayout);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	this->m_dev_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_dev_Context->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	this->m_dev_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->m_dev_Context->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	UINT numberOfViewports = 1;
	this->m_dev_Context->RSSetViewports(numberOfViewports, &vp);
}

void DeviceContext::createShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	this->m_d3dDevice->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	this->m_d3dDevice->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
}

void DeviceContext::setShaders()
{
	m_dev_Context->VSSetShader(m_vs, nullptr, 0);
	m_dev_Context->PSSetShader(m_ps, nullptr, 0);
}

void DeviceContext::getShaderBufferAndSize(void ** bytecode, UINT * size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();
}
