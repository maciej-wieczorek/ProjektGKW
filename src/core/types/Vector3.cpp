#include "Vector3.h"

const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);
const Vector3 Vector3::forward = Vector3(0, 0, 1);
const Vector3 Vector3::back = Vector3(0, 0, -1);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::zero = Vector3(0, 0, 0);
const Vector3 Vector3::one = Vector3(1, 1, 1);

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& other)
{
}

Vector3::Vector3(const glm::vec3& other)
{
}

Vector3::Vector3()
{
}

glm::vec3 Vector3::toVec3()
{
	return glm::vec3(x, y, z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}
