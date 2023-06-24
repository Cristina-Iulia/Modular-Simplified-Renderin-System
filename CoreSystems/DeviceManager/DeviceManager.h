#pragma once
#ifndef  DEV_M
#define DEV_M

#include <d3d11.h>
#include <d3dcompiler.h>
#include "spdlog/spdlog.h"

class DeviceManager
{
public:
	bool init();
	void relese();

	static DeviceManager* getInstance();

	// GETTER FUNCTIONS
	static ID3D11Device* getDevice();
	static IDXGIFactory* getFactory();
	static ID3D11DeviceContext* getDeviceContext();

private:
	DeviceManager();
	~DeviceManager();

	ID3D11Device* d3dDevice_ptr = nullptr;
	ID3D11DeviceContext* immediate_context = nullptr;
	D3D_FEATURE_LEVEL feature_level;
	IDXGIDevice*  dxgiDevice_ptr = nullptr;
	IDXGIAdapter* dxgiAdapter_ptr = nullptr;
	IDXGIFactory* dxgiFactory_ptr = nullptr;

};

#endif 