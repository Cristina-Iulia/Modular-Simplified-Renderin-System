#pragma once
#ifndef WND_DEF
#define WND_DEF

#include <Windows.h>
#include "../../spdlog-1.11.0/include/spdlog/spdlog.h"
#include "../../LowLevelRenderModule/Renderer/Renderer.h"
#include "../../MathLibrary/Vector3D.h"
#include "../../MathLibrary/Vector2D.h"
#include "../../MathLibrary/Matrix4x4.h"
#include "../../Interfaces/InputListener.h"
#include "../../InputSystem/InputSystem.h"
#include "../../ResourceManagerModule/ResourceGenerator.h"


class Window: public InputListener
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
	void onFocuse();
	void onLoseFocus();

	RECT getWindowRect();
	HWND getWindowDesc();
	void setHwnd(HWND hwnd);
	void setRenderer(Renderer* renderer);
	void setResourceGenerator(ResourceGenerator* generator);

	void update();

	// Inherited via InputListener
	virtual void keyDown(int key) override;
	virtual void keyUp(int key) override;
	virtual void onMouseMove(const Point& delta_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;


private:
	Renderer* sglRenderer;
	ResourceGenerator* sglResourceGenerator;


	void windowSettup();
	float old_delta = 0 ; // time for last frame
	float new_delta = 0; // time for current frame
	float delta_time = 0; // time between frames

	float delta_pos = 0;
	float delta_scale = 0;

	float rot_x = 0;
	float rot_y = 0;

	Matrix4x4 camera;
	float camera_Z = 0.0f;
	float camera_X = 0.0f;

	TexturePtr wood_tex = nullptr;
	MeshPtr mesh = nullptr;

protected:
	HWND m_hwnd;
	WNDCLASSEX wc;
	bool windowIsRunning;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

	float scale_cube = 1;


};

#endif