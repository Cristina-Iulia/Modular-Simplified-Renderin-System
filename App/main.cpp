#include "../CoreSystems/ControlModule/Controller.h"
#include "spdlog/spdlog.h"

int main()                                                                                                                                                                                                                                                                                                                 
{
	spdlog::info("In main()");
	Controller* app = Controller::getInstance();
	app->Startup();

	return 0;
}