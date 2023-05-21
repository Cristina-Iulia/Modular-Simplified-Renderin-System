#pragma once


class InputListener
{
public: 
	InputListener() {};
	~InputListener() {};

	//keyboard pure virtual callback functions
	virtual void keyDown(int key) = 0;
	virtual void keyUp(int key) = 0;

};