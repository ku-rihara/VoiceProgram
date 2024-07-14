#pragma once


class Vector2{

public:
	float x;
	float y;

public:

	Vector2();
    Vector2(float numX, float numY);

    Vector2 operator+(const Vector2& obj);

    Vector2 operator-(const Vector2& obj);

    Vector2 operator*(const Vector2& obj);

    Vector2 operator/(const Vector2& obj);

    void operator+=(const float& obj);

    void operator-=(const float& obj);

    void operator*=(const float& obj);

    void operator/=(const float& obj);
};

