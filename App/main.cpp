#include "../CoreSystems/ControlModule/Controller.h"
#include "spdlog/spdlog.h"
#include <iostream>

int main()                                                                                                                                                                                                                                                                                                                 
{

	Controller* app = Controller::getInstance();
	app->Startup();


	return 0;
}