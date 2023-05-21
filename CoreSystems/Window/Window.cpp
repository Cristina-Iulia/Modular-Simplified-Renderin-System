#include "Window.h"

static Window* wdSingleton = nullptr;

struct vertex
{
	Vector3D position;
	Vector3D position_after;
	Vector3D color;
	Vector3D color_sfter;
};

__declspec(align(16))
struct constant
{
public:
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
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
	//InputSystem::getInstance()->addListener(this);
}

void Window::onUpdate()
{
	//InputSystem::getInstance()->update();
	sglRenderer->clearRenderTarget(0,0,0,1);


	RECT rc = getWindowRect();
	sglRenderer->devContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	updateQuadPosition();

	sglRenderer->devContext->setVertexShader(sglRenderer->vertexShader);
	sglRenderer->devContext->setPixelShader(sglRenderer->pixelShader);

	sglRenderer->devContext->setConstantBuffer(sglRenderer->vertexShader, sglRenderer->constantBuffer);
	sglRenderer->devContext->setConstantBuffer(sglRenderer->pixelShader, sglRenderer->constantBuffer);


	sglRenderer->devContext->setVertexBuffer(sglRenderer->vertexBuffer);
	UINT listSize = sglRenderer->vertexBuffer->sizeOfList;
	sglRenderer->devContext->drawTriangleStrip(listSize, 0);

	sglRenderer->present(true);

	old_delta = new_delta;
	new_delta = ::GetTickCount();
	delta_time = (old_delta) ? ((new_delta - old_delta)/1000.0f)  : 0;
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
		{Vector3D (-0.5f,-0.5f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0),  Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),    Vector3D(-0.11f,0.78f,0.0f),    Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
		{Vector3D(0.5f,-0.5f,0.0f),     Vector3D(0.75f,-0.73f,0.0f),  Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(0.5f,0.5f,0.0f),      Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1) }
	};

	sglRenderer->createVertexBuffer();
	UINT listSize = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t shaderSize = 0;

	sglRenderer->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shaderSize);
	sglRenderer->createVertexShader(shader_byte_code, shaderSize);
	sglRenderer->vertexBuffer->init(list, sizeof(vertex), listSize, shader_byte_code, shaderSize);

	sglRenderer->releaseCompiledShader();

	sglRenderer->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &shaderSize);
	sglRenderer->createPixelShader(shader_byte_code, shaderSize);


	sglRenderer->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;
	sglRenderer->createConstantBuffer();
	sglRenderer->constantBuffer->init(&cc, sizeof(constant));
}

void Window::updateQuadPosition()
{
	constant cc;
	cc.m_angle = ::GetTickCount();

	auto rec = getWindowRect();
	auto width = (rec.right - rec.left)/400.0f;
	auto height = (rec.bottom - rec.top)/400.0f;


	delta_pos += delta_time / 4.0f;
	if (delta_pos > 1.0f)
	{
		delta_pos = 0;
	}

	Matrix4x4 temp;
	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), delta_pos));
	
	delta_scale += delta_time / 0.5f;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0 ), Vector3D(2, 2, 0), delta_pos));
	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(delta_scale)+1.0f)/2.0f));

	cc.m_world*=temp;
	cc.m_view.setIdentity();
	cc.m_proj.setProjectionORTH(width, height, -4.0f, 4.0f);
	

	sglRenderer->constantBuffer->update(reinterpret_cast<void *>(&cc));
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

void Window::keyDown(int key)
{
}

void Window::keyUp(int key)
{
}
