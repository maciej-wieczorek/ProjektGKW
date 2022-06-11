#pragma once

#include <iostream>

#include "../ComponentScript.h"
#include "../FrameStats.h"

class RotatorComponent : ComponentScript{
public:
	void Update();
private:
	int dir = 1;
	float speed = 2;
	float minx = -5;
	float maxx = 5;
};