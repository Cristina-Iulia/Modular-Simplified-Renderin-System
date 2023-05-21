#pragma once
#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "../Interfaces/InputListener.h"
#include <map>
#include <Windows.h>

class InputSystem
{
public:
	static InputSystem* getInstance();
	void init();
	void release();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void update();

private: 
	InputSystem();
	~InputSystem();

	std::map<InputListener*, InputListener*> listenerMap;
	unsigned char keysState[256] = {};
	unsigned char lastKeysState[256] = {};
};
#endif