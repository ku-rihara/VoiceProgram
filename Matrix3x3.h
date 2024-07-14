#pragma once
#include"Vector2C.h"

struct Matrix3x3 {

	float m[3][3];
};

Matrix3x3 MakeIdentity3x3();

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//Vertex Transform(Vertex VerTexWide, Matrix3x3 matrix);
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
Matrix3x3 MakeAffineMatrix(Vector2 scale, Vector2 rotate, Vector2 translate);

Matrix3x3 InverseMatrix(Matrix3x3 matrix);

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
Matrix3x3 MakeViewwportmatrix(float left, float top, float width, float height);

Matrix3x3 wvpVpMatrix(Matrix3x3 obj, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewport);


