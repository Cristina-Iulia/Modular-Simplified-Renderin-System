#include "../CoreSystems/ControlModule/Controller.h"
#include "spdlog/spdlog.h"

int main()                                                                                                                                                                                                                                                                                                                 
{
	spdlog::info("In main()");
	Controller* app = Controller::getInstance();
	spdlog::info("In main() PART 2");
	app->Startup();
	spdlog::info("In main() PART 3");

	return 0;
}