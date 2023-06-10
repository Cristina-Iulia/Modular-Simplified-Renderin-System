#pragma once

#include "../Resource.h"
#include <DirectXTex.h>
#include "../../CoreSystems/DeviceManager/DeviceManager.h"



class Texture : public Resource
{
public:
	Texture(const wchar_t * absolute_path);
	~Texture();

	ID3D11Resource * m_texture = nullptr;
	ID3D11ShaderResourceView *m_shader_res_view = nullptr;
	ID3D11SamplerState* sampler_state = nullptr;
};