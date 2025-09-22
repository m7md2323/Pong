#pragma once
#include<math.h>
class Vector2D
{
public:
	Vector2D(float x, float y) : xPos(x), yPos(y) {}

	float getX() { return xPos; }
	float getY() { return yPos; }

	void setX(float x) { xPos = x; }
	void setY(float y) { yPos = y; }
	//some Math operations on Vectors
	//length 
	float length() { return sqrt(xPos * xPos + yPos * yPos); }
	//addition using operator overloading
	Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(xPos + v2.xPos, yPos + v2.yPos);
	}
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.xPos += v2.xPos;
		v1.yPos += v2.yPos;
		return v1;
	}
	//multiplication operator overloading
	Vector2D operator*(float scalar)
	{
		return Vector2D(xPos * scalar, yPos * scalar);
	}
	Vector2D& operator*=(float scalar)
	{
		xPos *= scalar;
		yPos *= scalar;
		return *this;
	}
	//subtraction operator overloading
	Vector2D operator-(const Vector2D& v2) const
	{
		return Vector2D(xPos - v2.xPos, yPos - v2.yPos);
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.xPos -= v2.xPos;
		v1.yPos -= v2.yPos;
		return v1;
	}
	//division operator overloading
	Vector2D operator/(float scalar)
	{
		return Vector2D(xPos / scalar, yPos / scalar);
	}
	Vector2D& operator/=(float scalar)
	{
		xPos /= scalar;
		yPos /= scalar;
		return *this;
	}
	//to only care about the direction rather than the length, so we normalize its length to equal to 1 (unit vector)
	void normalize()
	{
		float l = length();
		if (l > 0) // we never want to attempt to divide by 0
		{
			(*this) *= 1 / l;
		}
	}
private:
	float xPos;
	float yPos;

};