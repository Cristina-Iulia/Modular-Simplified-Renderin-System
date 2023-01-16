#pragma once
#include <d3d11.h>

class Renderer
{
public:
	Renderer();
	~Renderer();
	bool init();
	bool release();
	static Renderer* getInstance();
	static Renderer* rdSingleton;

private:
	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_immContext;
	D3D_FEATURE_LEVEL m_feature_level;
};

