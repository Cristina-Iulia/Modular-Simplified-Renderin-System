#pragma once

#include "../../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();
	void init(void* indexList, UINT listSize);
	void release();

	ID3D11Buffer* buffer = 0;
	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA data = {};
	UINT sizeOfList;

private:
	void descriptorSetup(UINT listSize);
};