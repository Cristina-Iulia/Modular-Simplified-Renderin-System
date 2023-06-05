#include "MeshManager.h"

MeshManager::MeshManager() : ResourceManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::getMesh(const wchar_t * file_path)
{
	return std::static_pointer_cast<Mesh>(getResource(file_path));
}

Resource * MeshManager::createResource(const wchar_t * file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {}

	return mesh;
}
