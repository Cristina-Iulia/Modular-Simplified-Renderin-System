#pragma once
#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "../Interfaces/InputListener.h"
#include "../MathLibrary/Point.h"
#include "spdlog/spdlog.h"
#include <unordered_set>
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

	void handleLeftMouseDown();
	void handleLeftMouseUp();

	void handleRightMouseDown();
	void handleRightMouseUp();

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

	std::unordered_set<InputListener*> listenersSet;

private: 
	InputSystem();
	~InputSystem();

	// KEYBOARD HANDLING ATTRIBUTES

	unsigned char keysState[256] = {};
	unsigned char lastKeysState[256] = {};


	// MOUSE HANDLING ATTRIBUTES
	Point old_mouse_pos;



};
#endif