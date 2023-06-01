#pragma once

#include "../Include.h"
#include "../ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	TexturePtr getTexture(const wchar_t* file_path);
protected:
	virtual Resource* createResource(const wchar_t* file_path);

};
