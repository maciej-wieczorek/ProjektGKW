#pragma once

#include <glm/glm.hpp>

class Color {
public:
	static const Color white;
	static const Color black;
	static const Color red;
	static const Color green;
	static const Color blue;

	glm::vec4 vec4 = glm::vec4(1, 1, 1, 1);

	float* r = &vec4[0];
	float* g = &vec4[1];
	float* b = &vec4[2];
	float* a = &vec4[3];

	Color(float r, float g, float b, float a);
	Color();
};