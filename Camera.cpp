#include "Camera.h"

Camera::Camera()
{
	position = GatsMath::vec3(0.0f, 0.0f, 0.0f);
	up = GatsMath::vec3(0.0f, 1.0f, 0.0f);
	forward = GatsMath::vec3(0.0f, 0.0f, -1.0f);
	worldUp = up;
	yaw = -90.0f;
	pitch = 0.0f;
	moveSpeed = 3.0f;
	turnSpeed = 0.1f;

	std::cout << "Default Constructor" << std::endl;
	Update();
}

Camera::Camera(GatsMath::vec3 position, GatsMath::vec3 startUp, 
				float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed)
{
	this->position = position;
	this->up = startUp;
	this->worldUp = startUp;
	this->yaw = startYaw;
	this->pitch = startPitch;
	this->forward = GatsMath::vec3(0.0f, 0.0f, -1.0f);
	this->moveSpeed = startMoveSpeed;
	this->turnSpeed = startTurnSpeed;

	//std::cout << "Constructor" << std::endl;
	Update();
}

Camera::~Camera()
{
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	float velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position =  position + (forward * velocity);
	}

	if (keys[GLFW_KEY_S])
	{
		position = position - (forward * velocity);
	}

	if (keys[GLFW_KEY_A])
	{
		position  = position - (right * velocity);
	}

	if (keys[GLFW_KEY_D])
	{
		position = position + (right * velocity);
	}

	if (keys[GLFW_KEY_Q])
	{
		position = position + (up * velocity);
	}

	if (keys[GLFW_KEY_E])
	{
		position = position - (up * velocity);
	}

	//std::cout << "Camera Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;

	//std::cout << "Key Control" << std::endl;
	Update();
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	if (yaw < 0.0f)
	{
		yaw += 360.0f;
	}
	else if (yaw > 360.0f)
	{
		yaw -= 360.0f;
	}

	//std::cout << "Mouse Control" << std::endl;
	Update();
}

GatsMath::mat4 Camera::CalculateViewMatrix() const
{
	return GatsMath::lookAt<float>(position, position + forward, up);
}

void Camera::Update()
{
	forward.x = std::cos(GatsMath::ToRadians(yaw)) * std::cos(GatsMath::ToRadians(pitch));
	forward.y = std::sin(GatsMath::ToRadians(pitch));
	forward.z = std::sin(GatsMath::ToRadians(yaw)) * std::cos(GatsMath::ToRadians(pitch));
	forward = forward.normalize();

	std::cout << std::endl;
	std::cout << "[1] Position: " << position << std::endl;
	std::cout << "[2] Forward: " << forward << std::endl;
	std::cout << "[3] Up: " << up << std::endl;
	std::cout << "[4] Right: " << right << std::endl;
	std::cout << std::endl;

	right = GatsMath::cross(forward, worldUp).normalize();
	up = GatsMath::cross(right, forward).normalize();
}
