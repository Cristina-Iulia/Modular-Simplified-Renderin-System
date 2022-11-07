#pragma once
#include <Windows.h>


class Window
{
public:
	Window();
	~Window();
	bool init();
	bool release();
	bool broadcast();
	bool isRun();

	//EVENTS
	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy();


private:
	void windowSettup();
protected:
	HWND m_hwnd;
	WNDCLASSEX wc;
	bool windowIsRunning;

};

