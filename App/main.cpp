#include "../CoreSystems/ControlModule/Controller.h"
#include "spdlog/spdlog.h"

int main()                                                                                                                                                                                                                                                                                                                 
{
	spdlog::info("Ciocanul vesel");
	Controller* app = Controller::getInstance();
	app->Startup();

	return 0;
}