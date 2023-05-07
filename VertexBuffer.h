#pragma once

#include "CoreSystems/DeviceManager/DeviceManager.h"
#include "spdlog/spdlog.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void init(void* vertexList, UINT vertexSize, UINT listSize, void* shader_byte_code, size_t shader_size);
	void release();

	ID3D11Buffer* buffer = 0;
	ID3D11InputLayout* inputLayout = 0;
	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA data = {};
	UINT sizeOfVertex;
	UINT sizeOfList;

private:
	void descriptorSetup(UINT vertexSize, UINT listSize);
};

