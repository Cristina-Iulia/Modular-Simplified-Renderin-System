#include "Window.h"

static Window* wdSingleton = nullptr;

struct vertex
{
	Vector3D position;
	Vector2D textcoord;
};

__declspec(align(16))
struct constant
{
public:
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	Vector4D m_light_direction;
	Vector4D camera_pos;
};

Window::Window()
{
}

Window::~Window()
{
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
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
		case WM_SETFOCUS:
		{
			Window* window = (Window*)GetWindowLong(hwnd, GWLP_USERDATA);
			if (window) window->onFocuse();
			break;
		}
		case WM_KILLFOCUS:
		{
			Window* window = (Window*)GetWindowLong(hwnd, GWLP_USERDATA);
			if (window) window->onLoseFocus();
			break;
		}
		case WM_LBUTTONDOWN:
		{
			InputSystem::getInstance()->handleLeftMouseDown();
			break;
		}
		case WM_LBUTTONUP:
		{
			InputSystem::getInstance()->handleLeftMouseUp();
			break;
		}
		case WM_RBUTTONDOWN:
		{
			InputSystem::getInstance()->handleRightMouseDown();
			break;
		}
		case WM_RBUTTONUP:
		{
			InputSystem::getInstance()->handleRightMouseUp();
			break;
		}
		case WM_DESTROY:
		{
			// Event fired when the window is destroyed
			Window* window = (Window*)GetWindowLong(hwnd, GWLP_USERDATA);
			// On Destroy window Event
			if (window) window->onDestroy();
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
	InputSystem::getInstance()->showCursor(false);
}

void Window::onUpdate()
{
	InputSystem::getInstance()->update();
	sglRenderer->clearRenderTarget(0,0,0,1);


	RECT rc = getWindowRect();
	sglRenderer->devContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	sglRenderer->devContext->setVertexShader(sglRenderer->vertexShader);
	sglRenderer->devContext->setPixelShader(sglRenderer->pixelShader);

	sglRenderer->devContext->setConstantBuffer(sglRenderer->vertexShader, sglRenderer->constantBuffer);
	sglRenderer->devContext->setConstantBuffer(sglRenderer->pixelShader, sglRenderer->constantBuffer);
	sglRenderer->devContext->setTexture(sglRenderer->vertexShader, wood_tex);
	sglRenderer->devContext->setTexture(sglRenderer->pixelShader, wood_tex);


	sglRenderer->devContext->setVertexBuffer(mesh->getVertexBuffer());
	sglRenderer->devContext->setIndexBuffer(mesh->getIndexBuffer());


	sglRenderer->devContext->drawIndexedTriangleList(mesh->getIndexBuffer()->sizeOfList, 0, 0);

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

void Window::onFocuse()
{
	InputSystem::getInstance()->addListener(wdSingleton);
}

void Window::onLoseFocus()
{
	InputSystem::getInstance()->removeListener(wdSingleton);
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

	camera.setIdentity();
	camera.setTranslation(Vector3D(0, 0, -1));

	Vector3D position_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f) },
		{Vector3D(-0.5f,0.5f,-0.5f)},
		{ Vector3D(0.5f,0.5f,-0.5f)},
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f)},
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f)}
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f, 0.0f)},
		{ Vector2D(0.0f, 1.0f)},
		{ Vector2D(1.0f, 0.0f)},
		{ Vector2D(1.0f, 1.0f)}
	};

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};

	//sglRenderer->createVertexBuffer();

	UINT listSize = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	//sglRenderer->createIndexBuffer();
	//UINT indexListSize = ARRAYSIZE(index_list);

	//sglRenderer->indexBuffer->init(index_list, indexListSize);

	void* shader_byte_code = nullptr;
	size_t shaderSize = 0;


	sglRenderer->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shaderSize);
	sglRenderer->createVertexShader(shader_byte_code, shaderSize);
	//sglRenderer->vertexBuffer->init(vertex_list, sizeof(vertex), listSize, shader_byte_code, shaderSize);
	sglRenderer->releaseCompiledShader();

	sglRenderer->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &shaderSize);
	sglRenderer->createPixelShader(shader_byte_code, shaderSize);
	sglRenderer->releaseCompiledShader();

	constant cc;
	sglRenderer->createConstantBuffer();
	sglRenderer->constantBuffer->init(&cc, sizeof(constant));
}

void Window::setResourceGenerator(ResourceGenerator * generator)
{
	sglResourceGenerator = generator;

	wood_tex = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture,L"Assets\\Textures\\brick.png"));
	//TextureManager* textmng = new TextureManager();
	//wood_tex = textmng->getTexture(L"Assets\\Textures\\wood.jpg");

	if (wood_tex == nullptr)
	{
		spdlog::error("NO TEXTURE");
	}

	mesh = std::dynamic_pointer_cast<Mesh>(ResourceGenerator::getInstance()->getResource(R_Mesh, L"Assets\\Meshes\\statue.obj"));

	if (mesh == nullptr)
	{
		spdlog::error("NO MESH OBJ");
	}

	/*void* shader_byte_code = nullptr;
	size_t shaderSize = 0;

	sglRenderer->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &shaderSize);
	sglRenderer->createVertexMeshShader(shader_byte_code, shaderSize);
	sglRenderer->vertexMeshShader->init(&(mesh->getVertexList)[0], sizeof(VertexMesh), (UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	sglRenderer->releaseCompiledShader();*/
}

void Window::update()
{
	constant cc;


	delta_pos += delta_time / 10.0f;
	if (delta_pos > 1.0f)
	{
		delta_pos = 0;
	}

	Matrix4x4 temp;
	Matrix4x4 light_rot_matrix;
	light_rot_matrix.setIdentity();
	light_rot_matrix.setRotationY(light_rot_y);

	light_rot_y += 0.707f * delta_time;

	cc.m_light_direction = light_rot_matrix.getDirectionZ();
	
	delta_scale += delta_time / 0.55f;

	cc.m_world.setIdentity();

	Matrix4x4 cameraMartix;
	cameraMartix.setIdentity();
	temp.setRotationX(rot_x);
	cameraMartix *= temp;	

	temp.setIdentity();
	temp.setRotationY(rot_y);
	cameraMartix *= temp;

	Vector3D new_pos = camera.getTranslation() + cameraMartix.getDirectionZ() * (camera_Z * 0.3f);
	new_pos = new_pos + cameraMartix.getDirectionX() * (camera_X * 0.3f);


	cc.camera_pos = new_pos;

	cameraMartix.setTranslation(new_pos);

	camera = cameraMartix;
	cameraMartix.inverse();
	cc.m_view = cameraMartix;

	auto rec = getWindowRect();
	auto width = (rec.right - rec.left);
	auto height = (rec.bottom - rec.top);
	//cc.m_proj.setProjectionORTH(width, height, -4.0f, 4.0f);

	cc.m_proj.setProjectionPerspective(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	

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
	if (key == 'W')
	{
		//rot_x += 1.707*delta_time;
		camera_Z = 0.5f;
	}
	else if (key == 'S')
	{
		//rot_x -= 1.707*delta_time;
		camera_Z = -0.5f;
	}
	else if (key == 'A')
	{
		//rot_y += 1.707*delta_time;
		camera_X = -0.5f;
	}
	else if (key == 'D')
	{
		//rot_y -= 1.707*delta_time;
		camera_X = 0.5f;
	}
}

void Window::keyUp(int key)
{
	camera_Z = 0.0f;
	camera_X = 0.0f;
}

void Window::onMouseMove(const Point & delta_pos)
{
	auto rec = getWindowRect();
	auto width = (rec.right - rec.left);
	auto height = (rec.bottom - rec.top);

	rot_x += (delta_pos.y - (height/2.0f))*delta_time*0.2f;
	rot_y += (delta_pos.x - (width / 2.0f))*delta_time*0.2f;

	InputSystem::getInstance()->setCursorPosition(Point(width/2.0f, height/2.0f ));
}

void Window::onLeftMouseDown(const Point & mouse_pos)
{
	scale_cube = 0.5f;
}

void Window::onLeftMouseUp(const Point & mouse_pos)
{
	scale_cube = 1.0f;
}

void Window::onRightMouseDown(const Point & mouse_pos)
{
	scale_cube = 2.0f;
}

void Window::onRightMouseUp(const Point & mouse_pos)
{
	scale_cube = 1.0f;
}
