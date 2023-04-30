#pragma once

#include "CoreSystems/DeviceManager/DeviceManager.h"


class VertexShader
{
public:

	VertexShader();
	~VertexShader();

	void init(void* shaderByteCode, size_t byteCodeSize);
	void release();

	ID3D11VertexShader* getShader();

private:
	ID3D11VertexShader* shader = nullptr;
};

