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
	spdlog::info("In Controller::init()");
	sglWindow = Window::getInstance();
	if (!sglWindow->init()) {
		//some error log
	}
	
	sglDeviceManager = DeviceManager::getInstance();
	if (!sglDeviceManager->init()) {
		//some error log
	}


	sglRenderer = Renderer::getInstance();
	if (!sglRenderer->init())
	{
		//some error log
	}
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
	spdlog::info("In Controller::getInstance()");
	if (crtModule == nullptr)
	{
		spdlog::info("In Controller::getInstance() -> if");
		crtModule = new Controller();
		return crtModule;
	}
	else
	{
		spdlog::info("In Controller::getInstance() -> else");
		return crtModule;
	}

	spdlog::info("In Controller::getInstance() ->WRONG");
	return nullptr;
}
