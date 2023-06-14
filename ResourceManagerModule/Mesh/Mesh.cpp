#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Mesh::Mesh(const wchar_t * absolute_path) : Resource(absolute_path)
{
	tinyobj::attrib_t attribute;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(absolute_path);
	std::string mt_dir = inputfile.substr(0, inputfile.find_last_of("\\/"));

	bool res = tinyobj::LoadObj(&attribute, &shapes, &materials, &warn, &err, inputfile.c_str(), mt_dir.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	size_t full_size = 0;
	for (size_t s = 0; s < shapes.size(); s++)
	{
		full_size += shapes[s].mesh.indices.size();
	}

	list_vertices.reserve(full_size);
	list_indices.reserve(full_size);

	material_list.resize(materials.size());

	size_t index_global_offset = 0;

	for (size_t m = 0; m < materials.size(); ++m)
	{
		material_list[m].index_start = index_global_offset;
		material_list[m].material_id = m;

		for (size_t s = 0; s < shapes.size(); s++)
		{
			size_t index_offset = 0;


			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				if (shapes[s].mesh.material_ids[f] != m) continue;
				unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

				for (unsigned char v = 0; v < num_face_verts; v++)
				{
					tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

					tinyobj::real_t vx = attribute.vertices[index.vertex_index * 3 + 0];
					tinyobj::real_t vy = attribute.vertices[index.vertex_index * 3 + 1];
					tinyobj::real_t vz = attribute.vertices[index.vertex_index * 3 + 2];

					tinyobj::real_t tx = 0;
					tinyobj::real_t ty = 0;
					if (index.texcoord_index >= 0)
					{
						tx = attribute.texcoords[index.texcoord_index * 2 + 0];
						ty = attribute.texcoords[index.texcoord_index * 2 + 1];
					}

					tinyobj::real_t nx = attribute.normals[index.normal_index * 3 + 0];
					tinyobj::real_t ny = attribute.normals[index.normal_index * 3 + 1];
					tinyobj::real_t nz = attribute.normals[index.normal_index * 3 + 2];

					VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty), Vector3D(nx, ny, nz));
					list_vertices.push_back(vertex);

					list_indices.push_back((unsigned int)index_global_offset + v);
				}

				index_offset += num_face_verts;
				index_global_offset += num_face_verts;
			}
		}

		material_list[m].nr_elem_slot = index_global_offset - material_list[m].index_start;
	}

	

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderManager* shaderManager = ShaderManager::getInstance();
	shaderManager->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vertex_buffer = std::make_shared<VertexBuffer>();
	m_vertex_buffer->init(&list_vertices[0], sizeof(VertexMesh), (UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	m_index_buffer = std::make_shared <IndexBuffer>();
	m_index_buffer->init(&list_indices[0], (UINT)list_indices.size());
}

Mesh::~Mesh()
{
	m_vertex_buffer->release();
	m_index_buffer->release();
}

const VertexBufferPtr & Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

const IndexBufferPtr & Mesh::getIndexBuffer()
{
	return m_index_buffer;
}

const MaterialSlot & Mesh::getMaterialSlot(unsigned int slot)
{
	if (slot >= material_list.size())
	{
		spdlog::error("Material index outside of range");
		return MaterialSlot();
	}
	else return material_list[slot];
}

size_t Mesh::getNrMaterialSlots()
{
	return material_list.size();
}
