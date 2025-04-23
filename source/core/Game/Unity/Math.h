#pragma once
#include <math.h>
#include <cmath>

#define PI 3.14159265358979323846

struct Vector2
{
	float x, y;

	inline Vector2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
	inline Vector2 operator+(const Vector2& other) const { return { x + other.x, y + other.y }; }
	inline Vector2 operator-(const Vector2& other) const { return { x - other.x, y - other.y }; }
	inline Vector2 operator*(const Vector2& other) const { return { x * other.x, y * other.y }; }
	inline Vector2 operator/(const Vector2& other) const { return { x / other.x, y / other.y }; }
	inline Vector2 operator-() const { return { -x, -y }; }

	inline Vector2 normalized() const
	{
		float len = sqrtf(x * x + y * y);
		return { x / len, y / len };
	}

	inline float Length() {
		return std::sqrt(x * x + y * y);
	}

	inline Vector2 Normalize() {
		return Vector2(this->x / Length(), this->y / Length());
	}

	inline bool Empty() {
		return x == 0 && y == 0;
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}
};

struct Vector3
{
	float x, y, z;

	inline Vector3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
	inline Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
	inline Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
	inline Vector3 operator*(const Vector3& other) const { return { x * other.x, y * other.y, z * other.z }; }
	inline Vector3 operator/(const Vector3& other) const { return { x / other.x, y / other.y, z / other.z }; }
	inline Vector3 operator-() const { return { -x, -y, -z }; }
	inline Vector3& operator+=(const Vector3& other) { return *this = *this + other; }
	inline Vector3& operator-=(const Vector3& other) { return *this = *this - other; }

	inline Vector3 Normalized() const
	{
		float len = sqrtf(x * x + y * y + z * z);
		return { x / len, y / len, z / len };
	}

	inline float Magnitude()
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	inline Vector3 Normalize()
	{
		Vector3 out = *this;
		auto l = Magnitude();
		if (l == 0)
			return *this;
		;
		out.x /= l;
		out.y /= l;
		out.z /= l;
		return out;
	}

	inline float Dot(const Vector3& Vec2)
	{
		return this->x * Vec2.x + this->y * Vec2.y + this->z * Vec2.z;
	}

	static inline Vector3 Zero()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	inline bool Empty()
	{
		return x == 0 && y == 0 && z == 0;
	}

	inline float Distance(const Vector3& vector)
	{
		return std::sqrt(
			(x - vector.x) * (x - vector.x) +
			(y - vector.y) * (y - vector.y) +
			(z - vector.z) * (z - vector.z));
	}

	inline Vector3 Cross(const Vector3& other) const
	{
		return {
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
		};
	}

};

struct Vector4
{
	float x, y, z, w;

	inline Vector4 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
	inline Vector4 operator+(const Vector4& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	inline Vector4 operator-(const Vector4& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	inline Vector4 operator/(const Vector4& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
	inline Vector4 operator-() const { return { -x, -y, -z, -w }; }

	inline Vector4 operator*(const Vector4& other) const
	{
		return {
		w * other.x + x * other.w + y * other.z - z * other.y,
		w * other.y + y * other.w + z * other.x - x * other.z,
		w * other.z + z * other.w + x * other.y - y * other.x,
		w * other.w - x * other.x - y * other.y - z * other.z
		};
	}

	inline Vector3 operator*(const Vector3& vec) const
	{
		float _x = x * 2.0f;
		float _y = y * 2.0f;
		float _z = z * 2.0f;
		float xx = x * _x;
		float yy = y * _y;
		float zz = z * _z;
		float xy = x * _y;
		float xz = x * _z;
		float yz = y * _z;
		float wx = w * _x;
		float wy = w * _y;
		float wz = w * _z;

		Vector3 result;
		result.x = (1.0f - (yy + zz)) * vec.x + (xy - wz) * vec.y + (xz + wy) * vec.z;
		result.y = (xy + wz) * vec.x + (1.0f - (xx + zz)) * vec.y + (yz - wx) * vec.z;
		result.z = (xz - wy) * vec.x + (yz + wx) * vec.y + (1.0f - (xx + yy)) * vec.z;

		return result;
	}

	static inline Vector4 Euler(const Vector3& euler)
	{
		float cx = cosf(euler.x * 0.5f);
		float sx = sinf(euler.x * 0.5f);
		float cy = cosf(euler.y * 0.5f);
		float sy = sinf(euler.y * 0.5f);
		float cz = cosf(euler.z * 0.5f);
		float sz = sinf(euler.z * 0.5f);

		Vector4 q;
		q.w = cx * cy * cz + sx * sy * sz;
		q.x = sx * cy * cz - cx * sy * sz;
		q.y = cx * sy * cz + sx * cy * sz;
		q.z = cx * cy * sz - sx * sy * cz;
		return q;
	}

	static inline Vector4 FromEuler(const Vector3& euler)
	{
		float cx = cosf(euler.x * 0.5f);
		float sx = sinf(euler.x * 0.5f);
		float cy = cosf(euler.y * 0.5f);
		float sy = sinf(euler.y * 0.5f);
		float cz = cosf(euler.z * 0.5f);
		float sz = sinf(euler.z * 0.5f);

		Vector4 q;
		q.w = cx * cy * cz + sx * sy * sz;
		q.x = sx * cy * cz - cx * sy * sz;
		q.y = cx * sy * cz + sx * cy * sz;
		q.z = cx * cy * sz - sx * sy * cz;
		return q;
	}

	static inline Vector4 LookRotation(const Vector3& forward, const Vector3& up)
	{
		Vector3 f = forward.Normalized();
		Vector3 u = up.Normalized();
		Vector3 r = u.Cross(f).Normalized();
		u = f.Cross(r);

		float m00 = r.x, m01 = u.x, m02 = f.x;
		float m10 = r.y, m11 = u.y, m12 = f.y;
		float m20 = r.z, m21 = u.z, m22 = f.z;

		float trace = m00 + m11 + m22;
		Vector4 q;

		if (trace > 0.0f)
		{
			float s = sqrtf(trace + 1.0f) * 2.0f;
			q.w = 0.25f * s;
			q.x = (m21 - m12) / s;
			q.y = (m02 - m20) / s;
			q.z = (m10 - m01) / s;
		}
		else if ((m00 > m11) && (m00 > m22))
		{
			float s = sqrtf(1.0f + m00 - m11 - m22) * 2.0f;
			q.w = (m21 - m12) / s;
			q.x = 0.25f * s;
			q.y = (m01 + m10) / s;
			q.z = (m02 + m20) / s;
		}
		else if (m11 > m22)
		{
			float s = sqrtf(1.0f + m11 - m00 - m22) * 2.0f;
			q.w = (m02 - m20) / s;
			q.x = (m01 + m10) / s;
			q.y = 0.25f * s;
			q.z = (m12 + m21) / s;
		}
		else
		{
			float s = sqrtf(1.0f + m22 - m00 - m11) * 2.0f;
			q.w = (m10 - m01) / s;
			q.x = (m02 + m20) / s;
			q.y = (m12 + m21) / s;
			q.z = 0.25f * s;
		}

		return q;
	}


	inline Vector4 conjugate() const { return { -x, -y, -z, w }; }
};

struct Matrix4x4
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};