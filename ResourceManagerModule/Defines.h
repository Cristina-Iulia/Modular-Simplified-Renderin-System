#pragma once

#include <memory>

class Material;
class Texture;
class Resource;
class Mesh;

typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<Material> MaterialPtr;