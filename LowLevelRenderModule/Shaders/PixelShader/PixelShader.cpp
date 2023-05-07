#include "PixelShader.h"

PixelShader::PixelShader()
{
}

PixelShader::~PixelShader()
{
}

void PixelShader::init(void* shaderByteCode, size_t byteCodeSize)
{
	HRESULT result = DeviceManager::getDevice()->CreatePixelShader(shaderByteCode, byteCodeSize, nullptr, &shader);

	if (FAILED(result))
	{
		spdlog::critical("Shader of PixelShader creation UNSUCCESSFUL");
		spdlog::critical(HRESULT_CODE(result));
		exit(1);
	}
}

void PixelShader::release()
{
	shader->Release();
	delete this;
}

ID3D11PixelShader * PixelShader::getShader()
{
	if (!shader)
	{
		spdlog::critical("Shader of PixelShader retrieval UNSUCCESSFUL");
		exit(1);
	}
	return shader;
}
