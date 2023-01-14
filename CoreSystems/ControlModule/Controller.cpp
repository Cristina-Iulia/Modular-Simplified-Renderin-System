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
	if (!sglWindow->init()) {
		//some error log
	}
}

void Controller::release()
{
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
