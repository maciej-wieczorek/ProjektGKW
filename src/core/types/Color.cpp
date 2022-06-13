#include "Color.h"

const Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::blue = Color(0.0f, 0.0f, 1.0f, 1.0f);

Color::Color(float r, float g, float b, float a)
{
	this->vec4.r = r;
	this->vec4.g = g;
	this->vec4.b = b;
	this->vec4.a = a;
}

Color::Color()
{
}

glm::vec3 Color::getVec3()
{
	return glm::vec3(vec4.r, vec4.g, vec4.b);
}