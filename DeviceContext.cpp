#include "DeviceContext.h"


void DeviceContext::init()
{
	this->m_dev_Context = DeviceManager::getDeviceContext();
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
}
