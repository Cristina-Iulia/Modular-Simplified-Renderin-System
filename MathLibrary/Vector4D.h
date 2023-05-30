#pragma once
class Vector4D
{
public:
	Vector4D() : x(0), y(0), z(0), w(0) {}; // Default constructor
	Vector4D(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}; // Parametrized constructor
	Vector4D(const Vector4D& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}; // Copy constructor
	~Vector4D() {};

	void crossProd(Vector4D &v1, Vector4D &v2, Vector4D &v3)
	{
		this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z *v3.y);
		this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
		this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x *v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
		this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x *v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

	float x, y, z, w;
};