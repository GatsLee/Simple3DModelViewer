#include "Time.h"

float Time::deltaTime = 0.0f;
float Time::lastTime = 0.0f;
float Time::totalTimeElapsed = 0.0f;

void Time::UpdateTime()
{
	float time = static_cast<float>(glfwGetTime());
	deltaTime = time - lastTime;
	lastTime = time;
	totalTimeElapsed += deltaTime;
}