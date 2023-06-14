#pragma once
#include "../Resource.h"
#include <DirectXTex.h>
#include <locale>
#include <codecvt>
#include <vector>
#include "../../CoreSystems/DeviceManager/DeviceManager.h"
#include "../../MathLibrary/VertexMesh.h"
#include "../../LowLevelRenderModule/Shaders/ShaderManager/ShaderManager.h"
#include "../../MemoryBuffers/MemoryBufferLib.h"


//#define TINYOBJLOADER_IMPLEMENTATION
//#include <tiny_obj_loader.h>

struct MaterialSlot
{
	size_t index_start = 0;
	size_t nr_elem_slot = 0;
	size_t material_id = 0;

};

class Mesh : public Resource
{
public:
	Mesh(const wchar_t * absolute_path);
	~Mesh();
	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

	const MaterialSlot& getMaterialSlot(unsigned int slot);
	size_t getNrMaterialSlots();

private:

	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;
	std::vector<MaterialSlot> material_list;

};