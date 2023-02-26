#pragma once
#ifndef  DEV_M
#define DEV_M

#include <d3d11.h>
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

	ID3D11Device* m_d3dDevice = nullptr;
	ID3D11DeviceContext* m_immContext = nullptr;
	D3D_FEATURE_LEVEL m_feature_level;
	IDXGIDevice*  m_dxgiDevice = nullptr;
	IDXGIAdapter* m_dxgiAdapter = nullptr;
	IDXGIFactory* m_dxgiFactory = nullptr;

};

#endif 