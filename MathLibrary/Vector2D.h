#pragma once
class Vector2D
{
public:
	Vector2D() : u(0), v(0) {}; // Default constructor
	Vector2D(float u_, float v_) : u(u_), v(v_){}; // Parametrized constructor
	Vector2D(const Vector2D& vec) : u(vec.u), v(vec.v) {}; // Copv constructor
	~Vector2D() {};

	Vector2D operator+(const Vector2D other)
	{
		return Vector2D(u + other.u, v + other.v);
	}

	Vector2D operator*(const float scalar)
	{
		return Vector2D(u*scalar, v*scalar);
	}

	float u, v;
};