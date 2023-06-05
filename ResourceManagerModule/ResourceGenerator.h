#pragma once
#include "Include.h"
#include "ResourceManager.h"
#include "Texture/TextureManager.h"
#include "Mesh/MeshManager.h"

enum resource_type
{
	R_Texture,
	R_Mesh
};

class ResourceGenerator
{
public:
	~ResourceGenerator();
	static ResourceGenerator* getInstance();

	ResourcePtr getResource(resource_type type_, const wchar_t * file_path);

private:
	ResourceGenerator();

	TexturePtr getTexture(const wchar_t * file_path);
	MeshPtr getMesh(const wchar_t * file_path);



	TextureManager* textureManager = nullptr;
	MeshManager* meshManager = nullptr;
};