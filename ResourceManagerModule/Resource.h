#pragma once

#ifndef  RESOURCE_BASE
#define RESORESOURCE_BASEURCE

#include <memory>
#include <string>


class Resource
{
public:
	Resource(const wchar_t * absolute_path);
	virtual ~Resource();

protected:
	std::wstring absolute_path;
};

#endif