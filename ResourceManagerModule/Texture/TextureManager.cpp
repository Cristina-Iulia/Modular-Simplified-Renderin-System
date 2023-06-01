#include "TextureManager.h"

TextureManager::TextureManager(): ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::getTexture(const wchar_t * file_path)
{
	return std::static_pointer_cast<Texture>(getResource(file_path));
}

Resource * TextureManager::createResource(const wchar_t * file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}
