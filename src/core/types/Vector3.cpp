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

Vector3::Vector3(const Vector3& other) : Vector3(other.x, other.y, other.z)
{
}

Vector3::Vector3(const glm::vec3& other) : Vector3(other.x, other.y, other.z)
{
}

Vector3::Vector3() : Vector3(0, 0, 0)
{
}

glm::vec3 Vector3::toVec3()
{
	return glm::vec3(x, y, z);
}

Vector3 Vector3::normalized() const
{
	return (*this)/magnitude();
}

float Vector3::magnitude() const
{
	return sqrt(sqrMagnitude());
}

float Vector3::sqrMagnitude() const
{
	return x*x + y*y + z*z;
}

bool Vector3::strictEqual(const Vector3& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::approxEqual(const Vector3& other) const
{
	return (*this-other).magnitude() < 0.00001;
}

float Vector3::dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const
{
	return Vector3(y * other.z - z * other.y, z * other.x  - x * other.z, x * other.y - y * other.x);
}

bool Vector3::operator==(const Vector3& other) const
{
	return strictEqual(other);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !strictEqual(other);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const float f) const
{
	return Vector3(x * f, y * f, z * f);
}


Vector3 Vector3::operator/(const float f) const
{
	return Vector3(x / f, y / f, z / f);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}


Vector3& Vector3::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}
