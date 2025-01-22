#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}
}

// 2D Vector
class vector2
{
public:
	float x;
	float y;

	vector2(): x(0.0f), y(0.0f) {}
	explicit vector2(float inX, float inY): x(inX), y(inY) {}
	// Set both components in one line
	void set(float inX, float inY) { x = inX; y = inY; }

	// Vector addition (a + b)
	friend vector2 operator+(const vector2& a, const vector2& b)
	{
		return vector2(a.x + b.x, a.y + b.y);
	}

	// Vector subtraction (a - b)
	friend vector2 operator-(const vector2& a, const vector2& b)
	{
		return vector2(a.x - b.x, a.y - b.y);
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x*x + y*y);
	}

	static const vector2 Zero;

};

#endif
