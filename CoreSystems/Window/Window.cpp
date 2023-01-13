#include "Window.h"

Window* wdSingleton = nullptr;
Window::Window()
{
}

Window::~Window()
{
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// On Create window Event
		wdSingleton->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		// On Destroy window Event
		wdSingleton->onDestroy();
		::PostQuitMessage(0); // Make request to system to terminate process
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	windowSettup();

	if (!::RegisterClassEx(&wc))
	{
		return false;
	}


	if (!wdSingleton)
	{
		wdSingleton = this;
	}

	//Creation of window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "EngineWindow", "Graphic Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 786, NULL, NULL, NULL, NULL);

	if (!m_hwnd)
	{
		return false;
	}

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);


	windowIsRunning = true;

	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd))
	{
		return false;
	}
	return true;
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	wdSingleton->onUpdate();

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return windowIsRunning;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	windowIsRunning = false;
}

void Window::windowSettup()
{
	//Setting up WNDCLASSEX object

	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "EngineWindow";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;
}
