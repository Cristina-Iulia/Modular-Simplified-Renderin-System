#include "Controller.h"


static Controller* crtModule = nullptr;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init()
{
	spdlog::info("Initialising Controller");
	sglWindow = Window::getInstance();
	if (!sglWindow->init()) 
	{
		spdlog::critical("Window initialisation FAILED");
	}
	
	sglDeviceManager = DeviceManager::getInstance();
	if (!sglDeviceManager->init()) 
	{
		spdlog::critical("DeviceManager initialisation FAILED");
	}


	sglRenderer = Renderer::getInstance();
	if (!sglRenderer->init(sglWindow->getWindowDesc(), sglWindow->getWindowRect()))
	{
		spdlog::critical("Renderer initialisation FAILED");
	}

	sglWindow->setRenderer(sglRenderer);
	InputSystem::getInstance()->addListener(sglWindow);
}

void Controller::release()
{
	sglRenderer->release();
	sglDeviceManager->relese();
	sglWindow->onDestroy();
}

void Controller::Startup()
{
	spdlog::info("In Controller::Startup()");
	this->init();

	while (this->sglWindow->isRun())
	{

		this->sglWindow->broadcast();
	}
}

void Controller::ShutDown()
{
	release();
}

Controller * Controller::getInstance()
{

	if (crtModule == nullptr)
	{

		crtModule = new Controller();
		return crtModule;
	}
	else
	{

		return crtModule;
	}


	return nullptr;
}
