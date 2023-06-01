#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::getResource(const wchar_t * file_path)
{
	std::wstring absolute_path = std::filesystem::absolute(file_path);

	auto it = resources_map.find(absolute_path);

	if (it != resources_map.end())
	{
		return it->second;
	}
	else
	{
		Resource* raw_res = this->createResource(absolute_path.c_str());

		if (raw_res)
		{
			ResourcePtr res(raw_res);
			resources_map[absolute_path] = res;
			//ResourcePtr res = std::make_shared<Resource>(raw_res);
			//resources_map.insert(std::make_pair(absolute_path, res));
			return res;

		}
	}

	return nullptr;
}
