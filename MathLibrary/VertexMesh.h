#pragma once

#include "Vector2D.h"
#include "Vector3D.h"

class VertexMesh
{
public:
	VertexMesh() : position(), texcoord() {}; // Default constructor
	VertexMesh(Vector3D position, Vector2D texcoord) : position(position), texcoord(texcoord) {}; // Parametrized constructor
	VertexMesh(const VertexMesh& vertex) : position(vertex.position), texcoord(vertex.texcoord) {}; // Copv constructor
	~VertexMesh() {};


	Vector3D position;
	Vector2D texcoord;
};