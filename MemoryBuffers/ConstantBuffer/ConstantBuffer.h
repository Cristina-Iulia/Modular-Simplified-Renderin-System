#pragma once


#include "../../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void init(void* buffer, UINT bufferSize);
	void update(void* buffer);
	void release();

	ID3D11Buffer* constBuffer = 0;
	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA data = {};

private:
	void descriptorSetup(UINT bufferSize);
	ID3D11DeviceContext* devContext = nullptr;
};

