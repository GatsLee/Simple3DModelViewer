#pragma once

#include <GLFW/glfw3.h>

class Time
{
public:
	static void UpdateTime();

	static float GetDeltaTime() { return deltaTime; }
	static float GetTotalTime(){ return totalTimeElapsed; }

private:
	static float deltaTime;
	static float lastTime;
	static float totalTimeElapsed;
};

