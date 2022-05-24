#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Vector3.h"

class Quaternion {
public:
	static const Quaternion identity;

	Quaternion(float x, float y, float z, float w); //direct values for quaternion representation
	Quaternion(float x, float y, float z); //rotation in euler angles in degrees
	Quaternion(Vector3 rotationAxis, float rotationAngle); //angle in degrees
	Quaternion();

	glm::quat q;

	void setEuler(float x, float y, float z); //in degrees
	Vector3 getEuler(); //in degrees

	glm::mat4 getRotationMatrix();
};