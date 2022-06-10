#pragma once

#include <cmath>

#include <glm/glm.hpp>

class Vector3 {
public:
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 zero;
	static const Vector3 one;

	float x, y, z;

	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);
	Vector3(const glm::vec3& other);
	Vector3();

	glm::vec3 toVec3();

	Vector3 normalized() const;
	float magnitude() const;
	float sqrMagnitude() const;
	bool strictEqual(const Vector3& other) const;
	bool approxEqual(const Vector3& other) const;
	float dot(const Vector3& other) const;
	Vector3 cross(const Vector3& other) const;


	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const float f) const;
	Vector3 operator/(const float f) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const float f);
	Vector3& operator/=(const float f);
};