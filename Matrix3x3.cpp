#include<Novice.h>
#include<assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include"Matrix3x3.h"

Matrix3x3 MakeIdentity3x3() {
	Matrix3x3 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;


	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 result;
	for (int row = 0; row < 3; ++row) {

		for (int column = 0; column < 3; ++column) {

			result.m[row][column] = matrix1.m[row][0] * matrix2.m[0][column] + matrix1.m[row][1] * matrix2.m[1][column] + matrix1.m[row][2] * matrix2.m[2][column];
		}
	}
	return result;
}

//Vertex Transform(Vertex VerTexWide, Matrix3x3 matrix) {
//
//	Vertex  result;
//
//	VerTexWide.LeftTop.x = -VerTexWide.LeftTop.x / 2;
//	VerTexWide.LeftTop.y = -VerTexWide.LeftTop.y / 2;
//	VerTexWide.RightTop.x = VerTexWide.RightTop.x / 2;
//	VerTexWide.RightTop.y = -VerTexWide.RightTop.y / 2;
//	VerTexWide.LeftBottom.x = -VerTexWide.LeftBottom.x / 2;
//	VerTexWide.LeftBottom.y = VerTexWide.LeftBottom.y / 2;
//	VerTexWide.RightBottom.x = VerTexWide.RightBottom.x / 2;
//	VerTexWide.RightBottom.y = VerTexWide.RightBottom.y / 2;
//
//	result.LeftTop.x = VerTexWide.LeftTop.x * matrix.m[0][0] + VerTexWide.LeftTop.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.LeftTop.y = VerTexWide.LeftTop.x * matrix.m[0][1] + VerTexWide.LeftTop.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float leftTopw = VerTexWide.LeftTop.x * matrix.m[0][2] + VerTexWide.LeftTop.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//
//	result.RightTop.x = VerTexWide.RightTop.x * matrix.m[0][0] + VerTexWide.RightTop.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.RightTop.y = VerTexWide.RightTop.x * matrix.m[0][1] + VerTexWide.RightTop.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float RightTopw = VerTexWide.RightTop.x * matrix.m[0][2] + VerTexWide.RightTop.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//
//	result.LeftBottom.x = VerTexWide.LeftBottom.x * matrix.m[0][0] + VerTexWide.LeftBottom.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.LeftBottom.y = VerTexWide.LeftBottom.x * matrix.m[0][1] + VerTexWide.LeftBottom.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float LeftBottomw = VerTexWide.LeftBottom.x * matrix.m[0][2] + VerTexWide.LeftBottom.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//
//	result.RightBottom.x = VerTexWide.RightBottom.x * matrix.m[0][0] + VerTexWide.RightBottom.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.RightBottom.y = VerTexWide.RightBottom.x * matrix.m[0][1] + VerTexWide.RightBottom.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float RightBottomw = VerTexWide.RightBottom.x * matrix.m[0][2] + VerTexWide.RightBottom.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//
//	assert(leftTopw != 0.0f);
//
//	result.LeftTop.x /= leftTopw;
//	result.LeftTop.y /= leftTopw;
//
//	assert(RightTopw != 0.0f);
//
//	result.LeftTop.x /= RightTopw;
//	result.LeftTop.y /= RightTopw;
//
//	assert(LeftBottomw != 0.0f);
//
//	result.LeftTop.x /= LeftBottomw;
//	result.LeftTop.y /= LeftBottomw;
//
//	assert(RightBottomw != 0.0f);
//
//	result.LeftTop.x /= RightBottomw;
//	result.LeftTop.y /= RightBottomw;
//
//	return result;
//}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];

	float w = result.x * matrix.m[0][2] + result.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	return result;
}

Matrix3x3 InverseMatrix(Matrix3x3 matrix) {

	float a = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	Matrix3x3 result;
	result.m[0][0] = 1 / fabsf(a) * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = 1 / fabsf(a) * (-(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]));
	result.m[0][2] = 1 / fabsf(a) * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	result.m[1][0] = 1 / fabsf(a) * (-(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));
	result.m[1][1] = 1 / fabsf(a) * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = 1 / fabsf(a) * (-(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]));
	result.m[2][0] = 1 / fabsf(a) * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = 1 / fabsf(a) * (-(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]));
	result.m[2][2] = 1 / fabsf(a) * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return result;
}

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {

	Matrix3x3 result;
	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0;
	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;
	return result;
}

Matrix3x3 MakeViewwportmatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result;
	result.m[0][0] = (right - left) / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = -((bottom - top) / 2);
	result.m[1][2] = 0;
	result.m[2][0] = left + ((right - left) / 2);
	result.m[2][1] = top + ((bottom - top) / 2);
	result.m[2][2] = 1;
	return result;

}

Matrix3x3 wvpVpMatrix(Matrix3x3 obj, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewport) {

	Matrix3x3 result;

	result = Multiply(obj, view);
	result = Multiply(result, ortho);
	result = Multiply(result, viewport);

	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {

	Matrix3x3 scaleMatirx;
	Matrix3x3 rotateMatirx;
	Matrix3x3 translateMatirx;
	Matrix3x3 SR;
	Matrix3x3 result;

	scaleMatirx.m[0][0] = scale.x;
	scaleMatirx.m[0][1] = 0;
	scaleMatirx.m[0][2] = 0;
	scaleMatirx.m[1][0] = 0;
	scaleMatirx.m[1][1] = scale.y;
	scaleMatirx.m[1][2] = 0;
	scaleMatirx.m[2][0] = 0;
	scaleMatirx.m[2][1] = 0;
	scaleMatirx.m[2][2] = 1;

	rotateMatirx.m[0][0] = cosf(rotate);
	rotateMatirx.m[0][1] = sinf(rotate);
	rotateMatirx.m[0][2] = 0;
	rotateMatirx.m[1][0] = -sinf(rotate);
	rotateMatirx.m[1][1] = cosf(rotate);
	rotateMatirx.m[1][2] = 0;
	rotateMatirx.m[2][0] = 0;
	rotateMatirx.m[2][1] = 0;
	rotateMatirx.m[2][2] = 1;

	translateMatirx.m[0][0] = 1.0f;
	translateMatirx.m[0][1] = 0.0f;
	translateMatirx.m[0][2] = 0.0f;
	translateMatirx.m[1][0] = 0.0f;
	translateMatirx.m[1][1] = 1.0f;
	translateMatirx.m[1][2] = 0.0f;
	translateMatirx.m[2][0] = translate.x;
	translateMatirx.m[2][1] = translate.y;
	translateMatirx.m[2][2] = 1.0f;

	SR = Multiply(scaleMatirx, rotateMatirx);
	result = Multiply(SR, translateMatirx);

	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2 scale, Vector2 rotate, Vector2 translate) {

	Matrix3x3 scaleMatirx;
	Matrix3x3 rotateMatirx;
	Matrix3x3 translateMatirx;
	Matrix3x3 SR;
	Matrix3x3 result;


	scaleMatirx.m[0][0] = scale.x;
	scaleMatirx.m[0][1] = 0;
	scaleMatirx.m[0][2] = 0;
	scaleMatirx.m[1][0] = 0;
	scaleMatirx.m[1][1] = scale.y;
	scaleMatirx.m[1][2] = 0;
	scaleMatirx.m[2][0] = 0;
	scaleMatirx.m[2][1] = 0;
	scaleMatirx.m[2][2] = 1;


	rotateMatirx.m[0][0] = rotate.x;
	rotateMatirx.m[0][1] = rotate.y;
	rotateMatirx.m[0][2] = 0;
	rotateMatirx.m[1][0] = -rotate.y;
	rotateMatirx.m[1][1] = rotate.x;
	rotateMatirx.m[1][2] = 0;
	rotateMatirx.m[2][0] = 0;
	rotateMatirx.m[2][1] = 0;
	rotateMatirx.m[2][2] = 1;


	translateMatirx.m[0][0] = 1.0f;
	translateMatirx.m[0][1] = 0.0f;
	translateMatirx.m[0][2] = 0.0f;
	translateMatirx.m[1][0] = 0.0f;
	translateMatirx.m[1][1] = 1.0f;
	translateMatirx.m[1][2] = 0.0f;
	translateMatirx.m[2][0] = translate.x;
	translateMatirx.m[2][1] = translate.y;
	translateMatirx.m[2][2] = 1.0f;



	SR = Multiply(scaleMatirx, rotateMatirx);
	result = Multiply(SR, translateMatirx);

	return result;
}