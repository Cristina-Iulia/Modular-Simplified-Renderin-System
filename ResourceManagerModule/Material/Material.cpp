#include "Material.h"
#include <exception>

Material::Material(const wchar_t * vertex_shader_path, const wchar_t * pixel_shader_path)
{
	void* shader_byte_code = nullptr;
	size_t shaderSize = 0;

	ShaderManager* shaderManager = ShaderManager::getInstance();

	shaderManager->compileVertexShader(vertex_shader_path, "vsmain", &shader_byte_code, &shaderSize);
	vertex_shader = shaderManager->createVertexShader(shader_byte_code, shaderSize);
	shaderManager->releaseCompiledShader();

	if (!vertex_shader) throw std::runtime_error("Material vertex shader not created");

	shaderManager->compilePixelShader(pixel_shader_path, "psmain", &shader_byte_code, &shaderSize);
	pixel_shader = shaderManager->createPixelShader(shader_byte_code, shaderSize);
	shaderManager->releaseCompiledShader();

	if (!pixel_shader) throw std::runtime_error("Material pixel shader not created");
}

Material::Material(const MaterialPtr & material)
{
	vertex_shader = material->vertex_shader;
	pixel_shader = material->pixel_shader;
}

Material::~Material()
{
	vertex_shader->release();
	pixel_shader->release();

}

void Material::addTexture(const TexturePtr & tex)
{
	textures.push_back(tex);
}

void Material::removeTexture(unsigned int index)
{
	if (index < this->textures.size())
	{
		textures.erase(textures.begin() + index);
	}
}

void Material::setData(void * data, unsigned int size)
{
	if (constant_buffer == nullptr)
	{
		constant_buffer = std::make_shared <ConstantBuffer>();
		constant_buffer->init(data, size);
	}
	else
	{
		constant_buffer->update(data);
	}
}

void Material::setCullMode(Cull_type mode)
{
	cull_mode = mode;
}

Cull_type Material::getCullMode()
{
	return cull_mode;
}
