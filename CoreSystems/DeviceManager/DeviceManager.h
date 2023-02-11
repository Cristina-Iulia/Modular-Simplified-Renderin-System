#pragma once
#ifndef  DEV_M
#define DEV_M

#include <d3d11.h>

class DeviceManager
{
public:
	DeviceManager();
	~DeviceManager();

	bool init();
	void relese();

	static DeviceManager* getInstance();

	// GETTER FUNCTIONS
	static ID3D11Device* getDevice();
	static IDXGIFactory* getFactory();

private:
	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_immContext;
	D3D_FEATURE_LEVEL m_feature_level;
	IDXGIDevice*  m_dxgiDevice;
	IDXGIAdapter* m_dxgiAdapter;
	IDXGIFactory* m_dxgiFactory;

};

#endif 