#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

namespace id {
namespace maths
{

struct Matrix4x4
{
	float val[16];

	static auto perspective(float,float,float,float) -> Matrix4x4;
	static auto translate(float,float,float) -> Matrix4x4;
	static auto scale(float,float,float) -> Matrix4x4;
	static auto rotateX(float) -> Matrix4x4;
	static auto rotateY(float) -> Matrix4x4;
	static auto rotateZ(float) -> Matrix4x4;

	static auto getMatrix() ->float;
	// auto getPosition() const -> Vector3;

	auto inverse() -> Matrix4x4;

	auto operator * (Matrix4x4 const&) const -> Matrix4x4;
	auto operator *= (Matrix4x4 const&) -> Matrix4x4;

	static Matrix4x4 identity;
};

typedef Matrix4x4 Matrix4;

}
}

#endif
