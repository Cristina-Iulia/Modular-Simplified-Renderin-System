#pragma once
#ifndef  RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <unordered_map>
#include <string>
#include <filesystem> 
#include "Include.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	ResourcePtr getResource (const wchar_t * file_path);
protected:
	virtual Resource* createResource(const wchar_t * file_path) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> resources_map;
};



#endif