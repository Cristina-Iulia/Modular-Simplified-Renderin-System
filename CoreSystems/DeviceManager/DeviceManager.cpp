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
	UINT nufeature_levels = ARRAYSIZE(feature_levels);
	HRESULT res = 0;


	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			nufeature_levels, D3D11_SDK_VERSION, &d3dDevice_ptr, &feature_level, &immediate_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}

	if (FAILED(res))
	{
		spdlog::info("Device Creation FAILED");
		return false;
	}

	d3dDevice_ptr->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice_ptr);
	dxgiDevice_ptr->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter_ptr);
	dxgiAdapter_ptr->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory_ptr);

	spdlog::info("Device Creation SUCCESS");
	return true;
}

void DeviceManager::relese()
{
	spdlog::info("Destroy DeviceManager : RELEASE resources");
	immediate_context->Release();
	dxgiDevice_ptr->Release();
	dxgiAdapter_ptr->Release();
	dxgiFactory_ptr->Release();
	d3dDevice_ptr->Release();
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
	if (dvmSingleton->dxgiFactory_ptr == nullptr)
	{
		spdlog::info("ERROR AT : DeviceManager::FACTORY retrieval");
	}
	else
	{
		spdlog::info("Retrieve DeviceManager::FACTORY");
		return dvmSingleton->dxgiFactory_ptr;
	}

	spdlog::info("ERROR AT : DeviceManager::FACTORY retrieval");
	return nullptr;
}

ID3D11DeviceContext * DeviceManager::getDeviceContext()
{

	if (dvmSingleton->immediate_context == nullptr)
	{
		spdlog::info("ERROR AT : DeviceManager::CONTEXT retrieval");
	}
	else
	{
		spdlog::info("Retrieve DeviceManager::CONTEXT");
		return dvmSingleton->immediate_context;
	}

	spdlog::info("ERROR AT : DeviceManager::CONTEXT retrieval");
	return nullptr;
}

ID3D11Device* DeviceManager::getDevice()
{
	if (dvmSingleton->d3dDevice_ptr == nullptr)
	{
		spdlog::info("ERROR AT : DeviceManager::DEVICE retrieval");
	}
	else
	{
		spdlog::info("Retrieve DeviceManager::DEVICE");
		return dvmSingleton->d3dDevice_ptr;
	}

	spdlog::info("ERROR AT : DeviceManager::DEVICE retrieval");
	return nullptr;
}