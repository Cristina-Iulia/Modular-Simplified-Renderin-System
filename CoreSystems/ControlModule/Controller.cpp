#include "Controller.h"

Controller* Controller::crtModule = NULL;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init()
{
	sglWindow = Window::getInstance();
	sglRenderer = Renderer::getInstance();
	sglDeviceManager = DeviceManager::getInstance();
	
	if (!sglDeviceManager->init()) {
		//some error log
	}
	else if (!sglWindow->init()) {
		//some error log
	}
	else if (!sglRenderer->init())
	{
		//some error log
	}
}

void Controller::release()
{
	sglWindow->onDestroy();
	sglRenderer->release();
	sglDeviceManager->relese();
}

void Controller::Startup()
{
	crtModule->init();

	while (crtModule->sglWindow->isRun())
	{

		crtModule->sglWindow->broadcast();
	}
}

void Controller::ShutDown()
{
	release();
}

Controller * Controller::getInstance()
{
	if (crtModule == NULL)
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