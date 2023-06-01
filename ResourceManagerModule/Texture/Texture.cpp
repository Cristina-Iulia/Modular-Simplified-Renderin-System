#include "Texture.h"

Texture::Texture(const wchar_t * absolute_path): Resource(absolute_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(absolute_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (FAILED(res))
	{
		throw std::exception("Texture not created successfully");
	}
	else
	{
		res = DirectX::CreateTexture(DeviceManager::getDevice(), image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		DeviceManager::getDevice()->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);
	}
}

Texture::~Texture()
{
	m_texture->Release();
	m_shader_res_view->Release();
}
