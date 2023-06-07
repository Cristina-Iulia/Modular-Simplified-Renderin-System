#pragma once

#include "Vector2D.h"
#include "Vector3D.h"

class VertexMesh
{
public:
	VertexMesh() : position(), texcoord(), normal(){}; // Default constructor
	VertexMesh(Vector3D position, Vector2D texcoord, Vector3D normal) : position(position), texcoord(texcoord), normal(normal){}; // Parametrized constructor
	VertexMesh(const VertexMesh& vertex) : position(vertex.position), texcoord(vertex.texcoord), normal(vertex.normal){}; // Copv constructor
	~VertexMesh() {};


	Vector3D position;
	Vector2D texcoord;
	Vector3D normal;
};