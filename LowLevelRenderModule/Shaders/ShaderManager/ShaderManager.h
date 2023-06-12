#pragma once
#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include "../PixelShader/PixelShader.h"
#include  "../VertexShader/VertexShader.h"

typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;

class ShaderManager
{
public:


	~ShaderManager();
	static ShaderManager* getInstance();

	// CREATE SHADER --- CREATE SHADER --- CREATE SHADER --- CREATE SHADER --- CREATE SHADER
	VertexShaderPtr createVertexShader(void* shaderByteCode, size_t byteCodeSize);
	PixelShaderPtr createPixelShader(void* shaderByteCode, size_t byteCodeSize);


	// COMPILE SHADER --- COMPILE SHADER --- COMPILE SHADER --- COMPILE SHADER --- COMPILE SHADER
	void compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void compilePixelShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();

private:
	ID3DBlob* m_blob = nullptr;
	ShaderManager();
};

#endif