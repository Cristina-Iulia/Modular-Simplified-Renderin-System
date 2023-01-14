#pragma once
#include <Windows.h>


class Window
{
public:
	Window();
	~Window();
	bool init(); //initialize window
	bool release(); //destroy window
	bool broadcast(); //pick msg from system and despach them
	bool isRun();
	static Window* wdSingleton;
	static Window* getInstance();

	//EVENTS
	void onCreate();
	void onUpdate();
	void onDestroy();


private:
	void windowSettup();
protected:
	HWND m_hwnd;
	WNDCLASSEX wc;
	bool windowIsRunning;


};

