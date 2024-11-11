#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GatsMath.h"


class Camera
{
public:
	Camera();
	Camera(GatsMath::vec3 position, GatsMath::vec3 startUp, 
			float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
	~Camera();

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);

	GatsMath::vec3 GetCameraPosition() const { return position; }
	GatsMath::vec3 GetCameraDirection() const { return forward; }

	GatsMath::mat4 CalculateViewMatrix() const;

	void Update();

private:
	GatsMath::vec3 position;
	GatsMath::vec3 forward;
	GatsMath::vec3 up;
	GatsMath::vec3 right;
	GatsMath::vec3 worldUp;

	float yaw;
	float pitch;

	float moveSpeed;
	float turnSpeed;

};

