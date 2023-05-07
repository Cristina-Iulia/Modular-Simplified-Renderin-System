#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer()
{
	devContext = DeviceManager::getDeviceContext();
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::init(void* buffer, UINT bufferSize)
{

	descriptorSetup(bufferSize);

	data.pSysMem = buffer;
	
	HRESULT result = DeviceManager::getDevice()->CreateBuffer(&buffer_desc, &data, &constBuffer);

	if (FAILED(result))
	{
		spdlog::critical("Buffer of ConstantBuffer creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}

}

void ConstantBuffer::update(void* buffer)
{
	devContext->UpdateSubresource(constBuffer, NULL, NULL, buffer, NULL, NULL);
}

void ConstantBuffer::release()
{
	if(constBuffer)
		constBuffer->Release();
	delete this;
}

void ConstantBuffer::descriptorSetup(UINT bufferSize)
{
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.ByteWidth = bufferSize;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
}
