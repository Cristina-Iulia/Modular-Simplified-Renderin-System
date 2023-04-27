#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::init(void* vertexList, UINT vertexSize, UINT listSize, void* shader_byte_code, UINT shader_size)
{

	//if (buffer) buffer->Release();
	//if (inputLayout) inputLayout->Release();


	this->sizeOfVertex = vertexSize;
	this->sizeOfList = listSize;
	this->data.pSysMem = vertexList;
	this->data.SysMemPitch = 0;
	this->data.SysMemSlicePitch = 0;
	this->descriptorSetup(sizeOfVertex, sizeOfList);
	HRESULT result = DeviceManager::getDevice()->CreateBuffer(&buffer_desc, &data, &buffer);

	if (FAILED(result))
	{
		spdlog::critical("Buffer of VertexBuffer creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
	}

	D3D11_INPUT_ELEMENT_DESC layout[]=
	{
		{
		"POSITION",						// semantic name
		0,								// semantic index
		DXGI_FORMAT_R32G32B32_FLOAT,	// format
		0,								// input slot
		0,								// aligned byte ofset
		D3D11_INPUT_PER_VERTEX_DATA,	// input slot class
		0								// instance data step rate
		}
	};

	UINT layoutSize = ARRAYSIZE(layout);

	HRESULT layoutResult = DeviceManager::getDevice()->CreateInputLayout(layout, layoutSize, shader_byte_code, shader_size, &inputLayout);

	if (FAILED(layoutResult))
	{
		spdlog::critical("InputLayout of VertexBuffer creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(layoutResult));
	}
}

void VertexBuffer::release()
{
	buffer->Release();
	inputLayout->Release();
	delete this;
}

void VertexBuffer::descriptorSetup(UINT vertexSize, UINT listSize)
{
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.ByteWidth = (vertexSize * listSize);
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
}
