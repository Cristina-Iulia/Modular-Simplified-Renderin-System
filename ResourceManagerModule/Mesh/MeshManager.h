#pragma once

#include "../Include.h"
#include "../ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	MeshPtr getMesh(const wchar_t* file_path);
protected:
	virtual Resource* createResource(const wchar_t* file_path);

};