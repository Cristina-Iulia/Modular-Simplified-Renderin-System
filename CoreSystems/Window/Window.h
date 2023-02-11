#pragma once
#ifndef WND_DEF
#define WND_DEF
#include <Windows.h>
#include "spdlog/spdlog.h"


class Window
{
public:
	Window();
	~Window();
	bool init(); //initialize window
	bool release(); //destroy window
	bool broadcast(); //pick msg from system and despach them
	bool isRun();
	static Window* getInstance();

	//EVENTS
	void onCreate();
	void onUpdate();
	void onDestroy();

	RECT getWindowRect();
	HWND getWindowDesc();
	void setHwnd(HWND hwnd);

private:
	void windowSettup();
protected:
	HWND m_hwnd;
	WNDCLASSEX wc;
	bool windowIsRunning;


};

#endif