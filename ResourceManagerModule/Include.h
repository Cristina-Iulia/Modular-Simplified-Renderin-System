
#ifndef  RESOURCE_MANAGER_RESOURCES
#define RESOURCE_MANAGER_RESOURCES

#pragma once
#include <memory>
#include "Texture/Texture.h"
#include "Mesh/Mesh.h"
#include "Material/Material.h"


typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<Material> MaterialPtr;

#endif