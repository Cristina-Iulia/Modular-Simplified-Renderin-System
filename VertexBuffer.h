#pragma once

#include "CoreSystems/DeviceManager/DeviceManager.h"
#include "spdlog/spdlog.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void init(void* vertexList, UINT vertexSize, UINT listSize);
	void release();
private:
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA data = {};
	UINT sizeOfVertex;
	UINT sizeOfList;

private:
	void descriptorSetup(UINT vertexSize, UINT listSize);
};

