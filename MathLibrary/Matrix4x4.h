#pragma once
#include "IMatrix.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "spdlog/spdlog.h"

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
		data[3][0] = trn_.x;
		data[3][1] = trn_.y;
		data[3][2] = trn_.z;
	}

	void setProjectionPerspective(float fov, float aspect, float z_near, float z_far)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		data[0][0] = xscale;
		data[1][1] = yscale;
		data[2][2] = z_far / (z_far - z_near);
		data[2][3] = 1.0f;
		data[3][2] = (-z_near * z_far) / (z_far - z_near);
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

	void operator*=(const float scalar)
	{
		matrix_t::operator*=(scalar);
	}

	void operator=(const Matrix4x4& other)
	{
		matrix_t::operator=(other);
	}


	Vector3D getDirectionZ()
	{
		return Vector3D(data[2][0], data[2][1], data[2][2]);
	}

	Vector3D getDirectionX()
	{
		return Vector3D(data[0][0], data[0][1], data[0][2]);
	}

	Vector3D getTranslation()
	{
		return Vector3D(data[3][0], data[3][1], data[3][2]);
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = matrix_t::det();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->data[j][0]);
					vec[a].y = (this->data[j][1]);
					vec[a].z = (this->data[j][2]);
					vec[a].w = (this->data[j][3]);
				}
			}
			v.crossProd(vec[0], vec[1], vec[2]);

			out.data[0][i] = v.x;
			out.data[1][i] = v.y;
			out.data[2][i] = v.z;
			out.data[3][i] = v.w;

			out*=(pow(-1.0f, i) / det);
		}

		::memcpy(data, out.data, sizeof(float) * 16);
	}

	~Matrix4x4() {};
};