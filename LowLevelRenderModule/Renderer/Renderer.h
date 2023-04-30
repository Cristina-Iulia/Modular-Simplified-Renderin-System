#pragma once
#ifndef  LOW_LEVEL_RENDERER
#define LOW_LEVEL_RENDERER
#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../SwapChain/SwapChain.h"
#include <Windows.h>
#include "../../DeviceContext.h"
#include "../../VertexShader.h"
#include "spdlog/spdlog.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	bool init(HWND m_hwnd, RECT rc);
	bool release();
	static Renderer* getInstance();

	void clearRenderTarget(float red, float green, float blue, float alpha);
	void present(bool vsync);
	void createVertexBuffer();
	void compileVertexShader(const wchar_t* file, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();
	VertexShader* createVertexShader(void* shaderByteCode, size_t byteCodeSize);

	VertexBuffer* vertexBuffer;
	VertexShader* vertexShader;
	DeviceContext* devContext;
private:
	ID3DBlob* m_blob = nullptr;
	DeviceManager* sglDeviceManager;
	SwapChain* sglSwapChain;
	ID3D11RenderTargetView* renderTarget;


};

#endif