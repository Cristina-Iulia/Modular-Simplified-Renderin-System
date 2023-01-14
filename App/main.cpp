#include "../CoreSystems/ControlModule/Controller.h"

int main()                                                                                                                                                                                                                                                                                                                 
{
	Controller* app = Controller::getInstance();
	app->Startup();
	return 0;
}