#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::init(void* vertexList, UINT vertexSize, UINT listSize)
{
	this->sizeOfVertex = vertexSize;
	this->sizeOfList = listSize;
	this->data.pSysMem = vertexList;
	this->descriptorSetup(sizeOfVertex, sizeOfList);
	HRESULT result = DeviceManager::getDevice()->CreateBuffer(&buffer_desc, &data, &buffer);

	if (FAILED(result))
	{
		spdlog::critical("Buffer of VertexBuffer creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}
}

void VertexBuffer::release()
{
}

void VertexBuffer::descriptorSetup(UINT vertexSize, UINT listSize)
{
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.ByteWidth = (vertexSize * listSize);
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
}
