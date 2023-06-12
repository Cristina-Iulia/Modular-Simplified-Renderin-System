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
	float time_cloud = 0.0f;
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
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wdSingleton);
			wdSingleton->setHwnd(hwnd);
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
			Window* window = (Window*)GetWindowLong(hwnd, GWLP_USERDATA);
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
			spdlog::critical("In Window::getInstance wdSingleton ");
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
	sglRenderer->clearRenderTarget(0, 0.3f, 0.4f, 1);


	RECT rc = getWindowRect();
	sglRenderer->devContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	updateModel(Vector3D(0, 2, 0), object);
	drawMesh(mesh, object);

	updateModel(Vector3D(4, 2, 0), wall);
	drawMesh(monkey_mesh, wall);

	updateModel(Vector3D(0, 0, 0), brick);
	drawMesh(plane_mesh, brick);

	drawMesh(sky_mesh, env);

	sglRenderer->present(true);

	old_delta = new_delta;
	new_delta = ::GetTickCount();
	delta_time = (old_delta) ? ((new_delta - old_delta)/1000.0f)  : 0;
	time_cloud += delta_time;
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
	camera.setTranslation(Vector3D(0, -3, -2));
}

void Window::setResourceGenerator(ResourceGenerator * generator)
{
	sglResourceGenerator = generator;

	earth_tex = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture,L"Assets\\Textures\\earth_color.jpg"));
	earth_spec = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture, L"Assets\\Textures\\earth_spec.jpg"));
	earth_clouds = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture, L"Assets\\Textures\\clouds.jpg"));
	earth_night = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture, L"Assets\\Textures\\earth_night.jpg"));
	wall_tex = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture, L"Assets\\Textures\\wall.jpg"));
	brick_tex = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture, L"Assets\\Textures\\brick.png"));

	
	sky_tex = std::dynamic_pointer_cast<Texture>(ResourceGenerator::getInstance()->getResource(R_Texture, L"Assets\\Textures\\stars_map.jpg"));
	mesh = std::dynamic_pointer_cast<Mesh>(ResourceGenerator::getInstance()->getResource(R_Mesh, L"Assets\\Meshes\\sphere_hq.obj"));
	sky_mesh = std::dynamic_pointer_cast<Mesh>(ResourceGenerator::getInstance()->getResource(R_Mesh, L"Assets\\Meshes\\sphere.obj"));
	monkey_mesh = std::dynamic_pointer_cast<Mesh>(ResourceGenerator::getInstance()->getResource(R_Mesh, L"Assets\\Meshes\\suzanne.obj"));
	plane_mesh = std::dynamic_pointer_cast<Mesh>(ResourceGenerator::getInstance()->getResource(R_Mesh, L"Assets\\Meshes\\plane.obj"));

	object = sglResourceGenerator->getResource(R_Material, L"VertexShader.hlsl", L"PixelShader.hlsl");
	object->addTexture(earth_tex);
	object->addTexture(earth_spec);
	object->addTexture(earth_clouds);
	object->addTexture(earth_night);
	object->setCullMode(CULL_BACK);

	wall = sglResourceGenerator->getResource(R_Material, object);
	wall->addTexture(wall_tex);
	wall->setCullMode(CULL_BACK);

	brick = sglResourceGenerator->getResource(R_Material, object);
	brick->addTexture(brick_tex);
	brick->setCullMode(CULL_BACK);

	env = sglResourceGenerator->getResource(R_Material, L"VertexShader.hlsl", L"EnvPixelShader.hlsl");
	env->addTexture(sky_tex);
	env->setCullMode(CULL_FRONT);

}


void Window::drawMesh(const MeshPtr& mesh, const MaterialPtr& material)
{
	sglRenderer->devContext->setMaterial(material);


	sglRenderer->devContext->setVertexBuffer(mesh->getVertexBuffer());
	sglRenderer->devContext->setIndexBuffer(mesh->getIndexBuffer());


	sglRenderer->devContext->drawIndexedTriangleList(mesh->getIndexBuffer()->sizeOfList, 0, 0);

}

void Window::update()
{
	spdlog::info("UPDATE");
	updateCamera();
	updateLight();
	updateEnv();
}

void Window::updateCamera()
{
	Matrix4x4 cameraMartix, temp;
	cameraMartix.setIdentity();
	temp.setIdentity();
	temp.setRotationX(rot_x);
	cameraMartix *= temp;

	temp.setIdentity();
	temp.setRotationY(rot_y);
	cameraMartix *= temp;


	Vector3D new_pos = camera.getTranslation() + cameraMartix.getDirectionZ() * (camera_Z * 0.05f);
	new_pos = new_pos + cameraMartix.getDirectionX() * (camera_X * 0.05f);


	cameraMartix.setTranslation(new_pos);

	camera = cameraMartix;
	cameraMartix.inverse();
	camera_view = cameraMartix;

	auto rec = getWindowRect();
	auto width = (rec.right - rec.left);
	auto height = (rec.bottom - rec.top);

	camera_proj.setProjectionPerspective(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
}

void Window::updateModel(Vector3D position, const MaterialPtr& material)
{
	constant cc;

	Matrix4x4 light_rot_matrix;
	light_rot_matrix.setIdentity();
	light_rot_matrix.setRotationY(light_rot_y);

	Matrix4x4  temp;
	temp.setIdentity();
	temp.setRotationX(acos(-1));

	

	cc.m_world.setIdentity();
	cc.m_world.setTranslation(position);
	cc.m_world *= temp;
	cc.m_view = camera_view;
	cc.m_proj = camera_proj;
	cc.camera_pos = camera.getTranslation();
	cc.m_light_direction = light_rot_matrix.getDirectionZ();
	cc.time_cloud = time_cloud;

	material->setData(reinterpret_cast<void *>(&cc), sizeof(constant));
}

void Window::updateEnv()
{
	constant cc;

	cc.m_world.setIdentity();
	cc.m_world.setScale(Vector3D(100.0f, 100.0f, 100.0f));
	cc.m_world.setTranslation(camera.getTranslation());
	cc.m_view = camera_view;
	cc.m_proj = camera_proj;

	env->setData(reinterpret_cast<void *>(&cc), sizeof(constant));
}

void Window::updateLight()
{
	light_rot_y += 0.307f * delta_time;
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
