#pragma once
#include "../MathLibrary/Point.h"


class InputListener
{
public: 
	InputListener() {};
	~InputListener() {};

	//keyboard pure virtual callback functions
	virtual void keyDown(int key) = 0;
	virtual void keyUp(int key) = 0;

	//mouse pure virtual callback functions
	virtual void onMouseMove(const Point& delta_pos) = 0;

	virtual void onLeftMouseDown(const Point& mouse_pos) = 0;
	virtual void onLeftMouseUp(const Point& mouse_pos) = 0;

	virtual void onRightMouseDown(const Point& mouse_pos) = 0;
	virtual void onRightMouseUp(const Point& mouse_pos) = 0;

};