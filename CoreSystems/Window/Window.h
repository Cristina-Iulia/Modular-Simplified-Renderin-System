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
#include "../../ResourceManagerModule/Include.h"


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

	void drawMesh(const MeshPtr& mesh, const MaterialPtr& material); // to be moved

	void update();
	void updateCamera();
	void updateModel();
	void updateEnv();

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

	float rot_x = 0.0f;
	float rot_y = 0.0f;

	float light_rot_y = 0.0f;

	Matrix4x4 camera;
	Matrix4x4 camera_view;
	Matrix4x4 camera_proj;
	float camera_Z = 0.0f;
	float camera_X = 0.0f;

	TexturePtr earth_tex = nullptr;
	TexturePtr earth_spec = nullptr;
	TexturePtr earth_clouds = nullptr;
	TexturePtr earth_night = nullptr;
	TexturePtr sky_tex = nullptr;
	MeshPtr mesh = nullptr;
	MeshPtr sky_mesh = nullptr;

	VertexShaderPtr vertexShader = nullptr;
	VertexShaderPtr vertexMeshShader = nullptr;
	PixelShaderPtr pixelShader = nullptr;
	PixelShaderPtr envPixelShader = nullptr;

	MaterialPtr object;
	MaterialPtr env;

	float time_cloud = 0.0f;

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