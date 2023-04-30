#include "Window.h"

static Window* wdSingleton = nullptr;

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

Window::Window()
{
	//spdlog::info("In Window::Window() ");
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
		// Event fired when the window is created
		// collected here..
		//Window::wdSingleton = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wdSingleton);
		wdSingleton->setHwnd(hwnd);
		// On Create window Event
		wdSingleton->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLong(hwnd, GWLP_USERDATA);
		// On Destroy window Event
		window->onDestroy();
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
	this->onUpdate();

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return windowIsRunning;
}

Window* Window::getInstance()
{


	spdlog::info("In Window::getInstance");

	if (wdSingleton == nullptr)
	{
		wdSingleton = new Window();

		if (wdSingleton == nullptr) {
			spdlog::info("In Window::getInstance wdSingleton ");
		}
		return wdSingleton;
	}
	else
	{
		return wdSingleton;
	}

	return nullptr;
}

void Window::onCreate()
{
	
}

void Window::onUpdate()
{
	sglRenderer->clearRenderTarget(0,0,0,1);


	RECT rc = getWindowRect();
	sglRenderer->devContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	sglRenderer->devContext->setShaders();
	sglRenderer->devContext->setVertexShader(sglRenderer->vertexShader);
	sglRenderer->devContext->setVertexBuffer(sglRenderer->vertexBuffer);
	UINT listSize = sglRenderer->vertexBuffer->sizeOfList;
	sglRenderer->devContext->drawTriangleStrip(listSize, 0);

	sglRenderer->present(false);
}

void Window::onDestroy()
{
	if (this->release()) {
		windowIsRunning = false;
	}
	
}

RECT Window::getWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

HWND Window::getWindowDesc()
{
	return this->m_hwnd;
}

void Window::setHwnd(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::setRenderer(Renderer * renderer)
{
	sglRenderer = renderer;

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f}, // POS1
		{-0.5f,0.5f,0.0f}, // POS2
		{ 0.5f,-0.5f,0.0f },// POS2
		{ 0.5f,0.5f,0.0f}
	};

	sglRenderer->createVertexBuffer();
	UINT listSize = ARRAYSIZE(list);

	sglRenderer->devContext->createShaders();

	void* shader_byte_code = nullptr;
	size_t shaderSize = 0;
	sglRenderer->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shaderSize);

	sglRenderer->vertexShader  = sglRenderer->createVertexShader(shader_byte_code, shaderSize);
	sglRenderer->vertexBuffer->init(list, sizeof(vertex), listSize, shader_byte_code, shaderSize);

	sglRenderer->releaseCompiledShader();
	spdlog::info("List of vertexes : ", sglRenderer->vertexBuffer->data.pSysMem);
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
