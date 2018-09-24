#include <iostream>
#include <cmath>
#include <utility>

#include "maths/Matrix.h"
#include "maths/tools.h"

namespace id {
namespace maths {

float cotan(float x)
{
	return (1.f / std::tan(x));
}

Matrix4x4 Matrix4x4::identity =
{
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
};

auto Matrix4x4::perspective(float angle, float aspect, float near, float far) -> Matrix4x4
{

	float f = cotan(angle / 2);
	float z2 = (far + near) / (near - far);
	float z3 = (2 * far * near) / (near - far);

	return
	{
		(f / aspect), 0.f, 0.f, 0.f,
		0.f, f, 0.f, 0.f,
		0.f, 0.f, z2, z3,
		0.f, 0.f, -1.f, 0.f
	};
}

auto Matrix4x4::translate(float x, float y, float z) -> Matrix4x4
{
	return
	{
		1.f, 0.f, 0.f, x,
		0.f, 1.f, 0.f, y,
		0.f, 0.f, 1.f, z,
		0.f, 0.f, 0.f, 1.f
	};
}

auto Matrix4x4::scale(float x, float y, float z) -> Matrix4x4
{
	return
	{
		x, 0.f, 0.f, 0.f,
		0.f, y, 0.f, 0.f,
		0.f, 0.f, z, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

auto Matrix4x4::rotateX(float angle) -> Matrix4x4
{

	angle = deg2rad(angle);

	return
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, std::cos(angle), -std::sin(angle), 0.f,
		0.f, std::sin(angle), std::cos(angle), 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

auto Matrix4x4::rotateY(float angle) -> Matrix4x4
{
	angle = deg2rad(angle);

	return
	{
		std::cos(angle), 0.f, std::sin(angle), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-std::sin(angle), 0.f, std::cos(angle), 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

auto Matrix4x4::rotateZ(float angle) -> Matrix4x4
{
	angle = deg2rad(angle);

	return 
	{
		std::cos(angle), -std::sin(angle), 0.f, 0.f,
		std::sin(angle), std::cos(angle), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

auto Matrix4x4::inverse() -> Matrix4x4
{
	Matrix4x4 res = *this;

	for (int i = 3; i < 12; i += 4)
		res.val[i] *= -1;

	std::swap(res.val[1], res.val[4]);
	std::swap(res.val[2], res.val[8]);
	std::swap(res.val[6], res.val[9]);

	return res;
}

auto Matrix4x4::operator * (Matrix4x4 const& mat) const -> Matrix4x4
{
	Matrix4x4 res =
	{
		0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f
	};

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			for(int k = 0; k < 4; ++k)
			{
				res.val[(4*i) + j] += this->val[(4*i) + k] * mat.val[(4*k) + j];
			}

	return res;
}

auto Matrix4x4::operator *= (Matrix4x4 const& mat) -> Matrix4x4
{
	*this = *this * mat;

	return *this;
}

}
}
