/*
 Some operators of the Vector class based on
 operators of the Vector class by Bas Kuenen.
 Copyright (c) 2000 Bas Kuenen. All Rights Reserved.
 homepage: baskuenen.cfxweb.net
 */

#ifndef __VECTOR_H
#define __VECTOR_H

//#pragma pack(1)
#include <math.h>

#ifndef PI
#define PI			(3.14)
#endif
#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))

class Vector
{
public:
	float x;
	float y;
	float z;        // x,y,z coordinates

public:
	explicit Vector(float a = 0, float b = 0, float c = 0)
			: x(a), y(b), z(c)
	{
	}
	Vector(const Vector &v)
			: x(v.x), y(v.y), z(v.z)
	{
	}
	const Vector &operator=(const Vector &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	const bool operator==(const Vector &v) const
			{
		return ((x == v.x) && (y == v.y) && (z == v.z));
	}
	const bool operator!=(const Vector &v) const
			{
		return !(*this == v);
	}
	const Vector operator+(const Vector &v) const
			{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

//	// vector add (opposite of negation)
//	const Vector operator+() const
//	{
//		return Vector(*this);
//	}
	const Vector& operator+=(const Vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	const Vector operator-(const Vector& v) const
			{
		return Vector(x - v.x, y - v.y, z - v.z);
	}
	const Vector operator-() const
	{
		return Vector(-x, -y, -z);
	}
	const Vector &operator-=(const Vector& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	const Vector &operator*=(const float &s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	const Vector &operator/=(const float &s)
	{
		const float recip = 1 / s;        // for speed, one divecision
		x *= recip;
		y *= recip;
		z *= recip;
		return *this;
	}
	const Vector operator*(const float &s) const
			{
		return Vector(x * s, y * s, z * s);
	}
	friend inline const Vector operator*(const float &s, const Vector &v)
	{
		return v * s;
	}
	const Vector operator*(const Vector& v) const
			{
		return Vector(x * v.x, y * v.y, z * v.z);
	}
	// post multiply by scalar
	/*friend inline const Vector operator*(const Vector &v, const scalar_t &s)
	 {
	 return Vector(v.x*s, v.y*s, v.z*s);
	 }*/

	const Vector operator/(float s) const
			{
		s = 1 / s;
		return Vector(s * x, s * y, s * z);
	}
	// 向量积
	const Vector CrossProduct(const Vector &v) const
			{
		return Vector(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);
	}
	const Vector operator^(const Vector &v) const
			{
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	const float DotProduct(const Vector &v) const
			{
		return x * v.x + y * v.x + z * v.z;
	}
	const float operator%(const Vector &v) const
			{
		return x * v.x + y * v.x + z * v.z;
	}
	const float Length() const
	{
		return (float) sqrt((double) (x * x + y * y + z * z));
	}
	const Vector UnitVector() const
	{
		return (*this) / Length();
	}
	void Normalize()
	{
		(*this) /= Length();
	}
	const float operator!() const
	{
		return sqrtf(x * x + y * y + z * z);
	}
	const Vector operator |(const float length) const
			{
		return *this * (length / !(*this));
	}
	const Vector& operator |=(const float length)
	{
		return *this = *this | length;
	}
	const float inline Yaw(const Vector& normal) const
			{
		return acosf(*this % normal);
	}
	const Vector inline Reflection(const Vector& normal) const
			{
		const Vector v(*this | 1);        // normalize this vector
		return (v - normal * 2.0 * (v % normal)) * !*this;
	}
	const Vector inline Rotate(const float yaw, const Vector& normal) const
			{
		const float cosine = cosf(yaw);
		const float sine = sinf(yaw);

		return Vector(*this * cosine + ((normal * *this) * (1.0f - cosine)) *
				normal + (*this ^ normal) * sine);
	}
};

#endif
