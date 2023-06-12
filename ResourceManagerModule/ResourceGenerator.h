#pragma once
#include "Include.h"
#include "ResourceManager.h"
#include "Texture/TextureManager.h"
#include "Mesh/MeshManager.h"

enum resource_type
{
	R_Texture,
	R_Mesh,
	R_Material
};

class ResourceGenerator
{
public:
	~ResourceGenerator();
	static ResourceGenerator* getInstance();

	ResourcePtr getResource(resource_type type_, const wchar_t * file_path);
	MaterialPtr getResource(resource_type type_, const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_pat);
	MaterialPtr getResource(resource_type type_, const MaterialPtr& material);

private:
	ResourceGenerator();

	TexturePtr getTexture(const wchar_t * file_path);
	MeshPtr getMesh(const wchar_t * file_path);



	TextureManager* textureManager = nullptr;
	MeshManager* meshManager = nullptr;
};