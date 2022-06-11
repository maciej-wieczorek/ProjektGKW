#pragma once

#include "../Material.h"
#include"../types/Color.h"

class ColoredMaterial : Material{
public:
	ColoredMaterial(Color color);
	void setUniforms();
private:
	Color color;
};