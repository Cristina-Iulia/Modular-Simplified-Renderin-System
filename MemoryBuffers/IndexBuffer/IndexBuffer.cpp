#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::init(void* indexList, UINT listSize)
{

	if (buffer) buffer->Release();


	this->sizeOfList = listSize;
	this->data.pSysMem = indexList;
	this->descriptorSetup(sizeOfList);
	HRESULT result = DeviceManager::getDevice()->CreateBuffer(&buffer_desc, &data, &buffer);

	if (FAILED(result))
	{
		spdlog::critical("Buffer of IndexBuffer creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}

}

void IndexBuffer::release()
{
	buffer->Release();
	delete this;
}

void IndexBuffer::descriptorSetup( UINT listSize)
{
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.ByteWidth = (4 * listSize);
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
}
