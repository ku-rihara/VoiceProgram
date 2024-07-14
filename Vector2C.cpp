#include"Vector2C.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float numX,float numY) {
	x = numX;
	y = numY;
}


Vector2 Vector2:: operator+(const Vector2& obj) {

	Vector2 result;

	result.x = x + obj.x;
	result.y = y + obj.y;

	return result;

}

Vector2 Vector2:: operator-(const Vector2& obj) {

	Vector2 result;

	result.x = x - obj.x;
	result.y = y - obj.y;

	return result;

}

Vector2 Vector2:: operator*(const Vector2& obj) {

	Vector2 result;

	result.x = x * obj.x;
	result.y = y * obj.y;

	return result;

}

Vector2 Vector2:: operator/(const Vector2& obj) {

	Vector2 result;

	if (obj.x != 0){
		result.x = x / obj.x;
		
	}
	else {
		result.x = 0;
		
	}

	if (obj.y != 0) {
		result.y = y / obj.y;

	}
	else {
		result.y = 0;

	}

	return result;

}
void  Vector2::operator+=(const float& obj) {
     x +=obj;
	 y +=obj;
}

void Vector2:: operator-=(const float& obj) {
	x -= obj;
	y -= obj;
}

void  Vector2::operator*=(const float& obj) {
	x *= obj;
	y *= obj;
}

void  Vector2::operator/=(const float& obj) {
	if (obj != 0) {
		x /= obj;
		y /= obj;
	}
}