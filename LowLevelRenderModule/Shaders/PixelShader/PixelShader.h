#pragma once

#ifndef  PIXEL_SHADER
#define  PIXEL_SHADER

#include "../../../CoreSystems/DeviceManager/DeviceManager.h"


class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	void init(void* shaderByteCode, size_t byteCodeSize);
	void release();


	ID3D11PixelShader* getShader();

private:
	ID3D11PixelShader* shader = nullptr;
};

#endif