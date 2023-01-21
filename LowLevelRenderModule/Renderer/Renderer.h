#pragma once
#include "../../CoreSystems/DeviceManager/DeviceManager.h"

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
	DeviceManager* sglDeviceManager;

};

