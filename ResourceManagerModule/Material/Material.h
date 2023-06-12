#pragma once

#ifndef  MATERIAL
#define  MATERIAL

#include <vector>

#include "../../LowLevelRenderModule/Shaders/ShadersLib.h"
#include "../../LowLevelRenderModule/Shaders/ShaderManager/ShaderManager.h"
#include "../Texture/Texture.h"
#include "../../MemoryBuffers/MemoryBufferLib.h"

typedef std::shared_ptr<Texture> TexturePtr;

enum Cull_type
{
	CULL_FRONT,
	CULL_BACK
};

class Material
{
public:
	Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~Material();

	void addTexture(const TexturePtr& tex);
	void removeTexture(unsigned int index);
	void setData(void* data, unsigned int size);
	void setCullMode(Cull_type mode);
	Cull_type getCullMode();


	VertexShaderPtr vertex_shader = nullptr;
	PixelShaderPtr pixel_shader = nullptr;

	ConstantBufferPtr constant_buffer = nullptr;
	std::vector<TexturePtr> textures;

	Cull_type cull_mode = CULL_BACK;
};


#endif