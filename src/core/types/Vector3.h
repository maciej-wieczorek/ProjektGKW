//TODO: use glm::vec3 internally

#pragma once

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

	/*Vector3 normalized();
	float magnitude();
	float sqrMagnitude();
	bool strictEqual(const Vector3& other);
	bool approxEqual(const Vector3& other);
	Vector3 add(const Vector3& other);
	Vector3 subtract(const Vector3& other);
	Vector3 scale(const float f);
	Vector3 scale(const Vector3& other);
	float dot(const Vector3& other);
	Vector3 cross(const Vector3& other);


	bool operator==(const Vector3& other);
	bool operator!=(const Vector3& other);*/
	Vector3 operator+(const Vector3& other);
	/*Vector3 operator-(const Vector3& other);
	Vector3 operator*(const float f);
	Vector3 operator/(const float f);*/
};