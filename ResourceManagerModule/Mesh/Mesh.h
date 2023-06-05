#pragma once
#include "../Resource.h"
#include <DirectXTex.h>
#include <locale>
#include <codecvt>
#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../MathLibrary/VertexMesh.h"
#include "../../LowLevelRenderModule/Renderer/Renderer.h"


//#define TINYOBJLOADER_IMPLEMENTATION
//#include <tiny_obj_loader.h>



class Mesh : public Resource
{
public:
	Mesh(const wchar_t * absolute_path);
	~Mesh();
	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

	
private:

	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;

};