#include "ResourceGenerator.h"


static ResourceGenerator* resGenerator = nullptr;

ResourceGenerator::~ResourceGenerator()
{
}

ResourceGenerator * ResourceGenerator::getInstance()
{
	if (resGenerator == nullptr)
	{

		resGenerator = new ResourceGenerator();
		return resGenerator;
	}
	else
	{

		return resGenerator;
	}


	return nullptr;
}

ResourcePtr ResourceGenerator::getResource(resource_type type_, const wchar_t * file_path)
{
	switch (type_)
	{
	case R_Texture:
		return getTexture(file_path);
		break;

	case R_Mesh:
		return getMesh(file_path);
		break;

	default:
		spdlog::info("UNKNOWN RESOURCE REQUESTED");
	}

	return nullptr;
}

MaterialPtr ResourceGenerator::getResource(resource_type type_, const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_pat)
{
	if (type_ == R_Material)
	{
		MaterialPtr mt = nullptr;

		try
		{
			mt = std::make_shared<Material>(vertex_shader_path, pixel_shader_pat);
		}
		catch(...) {}

		return mt;
	}
	else
	{ 
		spdlog::info("UNKNOWN RESOURCE REQUESTED");
	}

	return nullptr;
}

MaterialPtr ResourceGenerator::getResource(resource_type type_, const MaterialPtr & material)
{
	if(type_ == R_Material)
	{
		MaterialPtr mt = nullptr;

		try
		{
			mt = std::make_shared<Material>(material);
		}
		catch (...) {}

		return mt;
	}
	else
	{
	spdlog::info("UNKNOWN RESOURCE REQUESTED");
	}

	return nullptr;
}

ResourceGenerator::ResourceGenerator()
{
}

TexturePtr ResourceGenerator::getTexture(const wchar_t * file_path)
{
	if (textureManager == nullptr)
	{
		textureManager = new TextureManager();
		if (!textureManager)
		{
			spdlog::info("Texture Manager initialisation FAILED");
		}
		else
		{
			spdlog::info("Texture Manager initialisation SUCCESSFUL");
		}
	}
		
	return textureManager->getTexture(file_path);
}

MeshPtr ResourceGenerator::getMesh(const wchar_t * file_path)
{
	if (meshManager == nullptr)
	{
		meshManager = new MeshManager();
		if (!meshManager)
		{
			spdlog::info("Texture Manager initialisation FAILED");
		}
		else
		{
			spdlog::info("Texture Manager initialisation SUCCESSFUL");
		}
	}

	return meshManager->getMesh(file_path);
}
