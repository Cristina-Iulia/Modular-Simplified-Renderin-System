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

	default:
		spdlog::critical("UNKNOWN RESOURCE REQUESTED");
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
			spdlog::critical("Texture Manager initialisation FAILED");
		}
		else
		{
			spdlog::info("Texture Manager initialisation SUCCESSFUL");
		}
	}
		
	return textureManager->getTexture(file_path);
}
