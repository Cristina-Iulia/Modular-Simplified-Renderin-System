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

	bool res = tinyobj::LoadObj(&attribute, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;


	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
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

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
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
