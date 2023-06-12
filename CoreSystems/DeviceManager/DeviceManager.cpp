#include "DeviceManager.h"

static DeviceManager* dvmSingleton = nullptr;

DeviceManager::DeviceManager()
{
	spdlog::info("Construct DeviceManager instance");
}

DeviceManager::~DeviceManager()
{
}

bool DeviceManager::init()
{
	spdlog::info("Initialising DeviceManager instance");
	D3D_DRIVER_TYPE driver_types[] = //array used to set driver in order from best to worst option 
	{
		D3D_DRIVER_TYPE_HARDWARE, //use GPU as main driver
		D3D_DRIVER_TYPE_WARP, //use CPU as main driver
		D3D_DRIVER_TYPE_REFERENCE //WARP with low performance
	};

	D3D_FEATURE_LEVEL feature_levels[] =
	{
	 D3D_FEATURE_LEVEL_11_0,
	 D3D_FEATURE_LEVEL_11_1
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);
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

	if (FAILED(res))
	{
		spdlog::info("Device Creation FAILED");
		return false;
	}

	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgiDevice);
	m_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgiAdapter);
	m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgiFactory);

	spdlog::info("Device Creation SUCCESS");
	return true;
}

void DeviceManager::relese()
{
	spdlog::info("Destroy DeviceManager : RELEASE resources");
	m_immContext->Release();
	m_dxgiDevice->Release();
	m_dxgiAdapter->Release();
	m_dxgiFactory->Release();
	m_d3dDevice->Release();
}

DeviceManager * DeviceManager::getInstance()
{
	spdlog::info("Retrieve DeviceManager instance");
	if (dvmSingleton == nullptr)
	{
		dvmSingleton = new DeviceManager();
		return dvmSingleton;
	}
	else
	{
		return dvmSingleton;
	}

	spdlog::info("ERROR AT : DeviceManager::INSTANCE retrieval");
	return nullptr;
}

IDXGIFactory * DeviceManager::getFactory()
{
	if (dvmSingleton->m_dxgiFactory == nullptr)
	{
		spdlog::info("ERROR AT : DeviceManager::FACTORY retrieval");
	}
	else
	{
		spdlog::info("Retrieve DeviceManager::FACTORY");
		return dvmSingleton->m_dxgiFactory;
	}

	spdlog::info("ERROR AT : DeviceManager::FACTORY retrieval");
	return nullptr;
}

ID3D11DeviceContext * DeviceManager::getDeviceContext()
{

	if (dvmSingleton->m_immContext == nullptr)
	{
		spdlog::info("ERROR AT : DeviceManager::CONTEXT retrieval");
	}
	else
	{
		spdlog::info("Retrieve DeviceManager::CONTEXT");
		return dvmSingleton->m_immContext;
	}

	spdlog::info("ERROR AT : DeviceManager::CONTEXT retrieval");
	return nullptr;
}

ID3D11Device* DeviceManager::getDevice()
{
	if (dvmSingleton->m_d3dDevice == nullptr)
	{
		spdlog::info("ERROR AT : DeviceManager::DEVICE retrieval");
	}
	else
	{
		spdlog::info("Retrieve DeviceManager::DEVICE");
		return dvmSingleton->m_d3dDevice;
	}

	spdlog::info("ERROR AT : DeviceManager::DEVICE retrieval");
	return nullptr;
}