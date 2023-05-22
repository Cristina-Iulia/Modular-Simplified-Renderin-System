#pragma once
#include "IMatrix.h"
#include "Vector3D.h"

class Matrix4x4: public matrix_t<float, 4, 4>
{
public:

	Matrix4x4() : matrix_t(){};

	void reset()
	{
		matrix_t::reset();
	}

	void setTranslation(const Vector3D& trn_)
	{
		setIdentity();
		data[3][0] = trn_.x;
		data[3][1] = trn_.y;
		data[3][2] = trn_.z;
	}

	void setProjectionORTH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		data[0][0] = 2.0f / width;
		data[1][1] = 2.0f / height;
		data[2][2] = 1.0f / (far_plane - near_plane);
		data[3][2] = -(near_plane / (far_plane - near_plane));
	}

	void setScale(const Vector3D& scale_)
	{
		setIdentity();
		data[0][0] = scale_.x;
		data[1][1] = scale_.y;
		data[2][2] = scale_.z;
	}

	void setRotationX(float x)
	{
		setIdentity();
		data[1][1] = cos(x);
		data[1][2] = sin(x);
		data[2][1] = -sin(x);
		data[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		setIdentity();
		data[0][0] = cos(y);
		data[0][2] = -sin(y);
		data[2][0] = sin(y);
		data[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		setIdentity();
		data[0][0] = cos(z);
		data[0][1] = sin(z);
		data[1][0] = -sin(z);
		data[1][1] = cos(z);
	}

	void operator*=(const Matrix4x4& other)
	{
		matrix_t::operator*=(other);
	}

	~Matrix4x4() {};
};