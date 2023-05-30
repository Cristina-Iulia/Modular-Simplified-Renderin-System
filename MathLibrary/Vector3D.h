#pragma once

class Vector3D
{
public:
	Vector3D(): x(0), y(0), z(0){}; // Default constructor
	Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}; // Parametrized constructor
	Vector3D(const Vector3D& vec) : x(vec.x), y(vec.y), z(vec.z) {}; // Copy constructor
	~Vector3D() {};

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D result;
		result.x = start.x *(1.0f - delta) + end.x * (delta);
		result.y = start.y *(1.0f - delta) + end.y * (delta);
		result.z = start.z *(1.0f - delta) + end.z * (delta);

		return result;
	}

	Vector3D operator+(const Vector3D other)
	{
		return Vector3D(x+other.x, y+other.y, z+other.z);
	}

	Vector3D operator*(const float scalar)
	{
		return Vector3D(x*scalar, y*scalar, z*scalar);
	}

	float x, y, z;
};