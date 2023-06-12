
#include "ShaderManager.h"


static ShaderManager* sglShaderManager = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

ShaderManager * ShaderManager::getInstance()
{
	if (sglShaderManager == nullptr)
	{
		sglShaderManager = new ShaderManager();
		return sglShaderManager;
	}
	else
	{
		return sglShaderManager;
	}

	return nullptr;

}

VertexShaderPtr ShaderManager::createVertexShader(void* shaderByteCode, size_t byteCodeSize)
{
	VertexShaderPtr vertexShader = std::make_shared <VertexShader>();
	vertexShader->init(shaderByteCode, byteCodeSize);
	return vertexShader;
}

PixelShaderPtr ShaderManager::createPixelShader(void* shaderByteCode, size_t byteCodeSize)
{
	PixelShaderPtr pixelShader = std::make_shared <PixelShader>();
	pixelShader->init(shaderByteCode, byteCodeSize);
	return pixelShader;
}

void ShaderManager::compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	//if (!(m_blob == nullptr))
		//m_blob->Release();
	HRESULT result = ::D3DCompileFromFile(file, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &m_blob, &error_blob);

	if (FAILED(result))
	{
		spdlog::info("VertexShader compilation UNSUCCESSFUL");
		spdlog::info(HRESULT_CODE(result));
		if (error_blob)
			error_blob->Release();
		exit(1);
	}

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void ShaderManager::compilePixelShader(const wchar_t * file, const char * entryPointName, void ** shaderByteCode, size_t * byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	if (m_blob)
		m_blob->Release();
	HRESULT result = ::D3DCompileFromFile(file, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &m_blob, &error_blob);

	if (FAILED(result))
	{
		spdlog::info("PixelShader compilation UNSUCCESSFUL");
		spdlog::info(HRESULT_CODE(result));
		if (error_blob)
			error_blob->Release();
		exit(1);
	}

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void ShaderManager::releaseCompiledShader()
{
	if (m_blob)
		m_blob->Release();
}