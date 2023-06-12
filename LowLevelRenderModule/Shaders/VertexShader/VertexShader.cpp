#include "VertexShader.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::init(void* shaderByteCode, size_t byteCodeSize)
{
	HRESULT result = DeviceManager::getDevice()->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &shader);

	if (FAILED(result))
	{
		spdlog::info("Shader of VertexShader creation UNSUCCESSFUL");
		spdlog::info(HRESULT_CODE(result));
		exit(1);
	}
}

void VertexShader::release()
{
	shader->Release();
	delete this;
}

ID3D11VertexShader * VertexShader::getShader()
{
	if (!shader)
	{
		spdlog::info("Shader of VertexShader retrieval UNSUCCESSFUL");
		exit(1);
	}
	return shader;
}
