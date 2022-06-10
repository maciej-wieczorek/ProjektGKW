#include "FrameStats.h"

float FrameStats::currentFrame = 0;
float FrameStats::lastFrame = 0;
float FrameStats::deltaTime = 0;
int FrameStats::framesCount = 0;
float FrameStats::currentFramerate = 0;


void FrameStats::registerFrame()
{
	++framesCount;
	lastFrame = currentFrame;
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	currentFramerate = 1 / deltaTime;
}

float FrameStats::getFramesCount()
{
	return framesCount;
}

float FrameStats::getCurrentFrameRate()
{
	return currentFramerate;
}

float FrameStats::getRunningTime()
{
	return glfwGetTime();
}

float FrameStats::getDeltaTime()
{
	return deltaTime;
}

float FrameStats::getFrameStartTime()
{
	return currentFrame;
}
