#include "Window.h"

static Window* wdSingleton = nullptr;

struct vertex
{
	Vector3D position;
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
	sglRenderer->devContext->setIndexBuffer(sglRenderer->indexBuffer);


	sglRenderer->devContext->drawIndexedTriangleList(sglRenderer->indexBuffer->sizeOfList, 0, 0);

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
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};

	sglRenderer->createVertexBuffer();
	UINT listSize = ARRAYSIZE(list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	sglRenderer->createIndexBuffer();
	UINT indexListSize = ARRAYSIZE(index_list);

	sglRenderer->indexBuffer->init(index_list, indexListSize);

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


	delta_pos += delta_time / 10.0f;
	if (delta_pos > 1.0f)
	{
		delta_pos = 0;
	}

	Matrix4x4 temp;
	
	delta_scale += delta_time / 0.55f;

	//cc.m_world*=temp;
	cc.m_world.setScale(Vector3D(1.0f, 1.0f, 1.0f));


	temp.setRotationZ(delta_scale);
	cc.m_world *= temp;

	//temp.reset();
	temp.setRotationY(delta_scale);
	cc.m_world *= temp;

	//temp.reset();
	temp.setRotationX(delta_scale);
	cc.m_world *= temp;



	cc.m_view.setIdentity();

	auto rec = getWindowRect();
	auto width = (rec.right - rec.left) / 300.0f;
	auto height = (rec.bottom - rec.top) / 300.0f;
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
