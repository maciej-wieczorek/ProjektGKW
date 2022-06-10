#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class FrameStats {
public:
	static void registerFrame();
	static float getFramesCount();
	static float getCurrentFrameRate();
	static float getRunningTime();
	static float getDeltaTime();
	static float getFrameStartTime();
private:
	static int framesCount;
	static float currentFramerate;
	static float deltaTime;
	static float currentFrame;
	static float lastFrame;
};