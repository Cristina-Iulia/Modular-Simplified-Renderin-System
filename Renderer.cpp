#include "Renderer.h"

//#define driver_types (D3D_DRIVER_TYPE[]) { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE}

Renderer* Renderer::rdSingleton = nullptr;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::init()
{
	D3D_DRIVER_TYPE driver_types[] = //array used to set driver in order from best to worst option 
	{
		D3D_DRIVER_TYPE_HARDWARE, //use GPU as main driver
		D3D_DRIVER_TYPE_WARP, //use CPU as main driver
		D3D_DRIVER_TYPE_REFERENCE //WARP with low performance
	};
	
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
	 D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3dDevice, &m_feature_level, &m_immContext);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}

	return true;
}

bool Renderer::release()
{
	m_immContext->Release();
	m_d3dDevice->Release();

	return true;
}

Renderer * Renderer::getInstance()
{
	if (Renderer::rdSingleton == nullptr)
	{
		Renderer::rdSingleton = new Renderer;
		return rdSingleton;
	}
	else
	{
		return rdSingleton;
	}

	return nullptr;
}
