#include "Window.h"

Window::Window(GLint width, GLint height)
{
	windowWidth = width;
	windowHeight = height;

	lastX = 0.0f;
	lastY = 0.0f;

	xChange = 0.0f;
	yChange = 0.0f;

	mouseFirstMoved = true;

	for (auto& i : keys)
	{
		i = false;
	}
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

bool Window::Initialize()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed!" << std::endl;
		glfwTerminate();
		return false;
	}

	// Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Allow Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(windowWidth, windowHeight, "3D Model Viewer by GatsLee", NULL, NULL);
	if (!mainWindow)
	{
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return false;
	}

	// Get buffer size information
	int tmpBufferWidth, tmpBufferHeight;
	glfwGetFramebufferSize(mainWindow, &tmpBufferWidth, &tmpBufferHeight);
	bufferHeight = static_cast<GLuint>(tmpBufferHeight);
	bufferWidth = static_cast<GLuint>(tmpBufferWidth);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	CreateCallbacks();
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	// setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return true;
}

GLfloat Window::GetXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::GetYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//std::cout << "Pressed: " << key << std::endl;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//std::cout << "Released: " << key << std::endl;
		}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = static_cast<GLfloat>(xPos);
		theWindow->lastY = static_cast<GLfloat>(yPos);
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = static_cast<GLfloat>(xPos) - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - static_cast<GLfloat>(yPos);

	theWindow->lastX = static_cast<GLfloat>(xPos);
	theWindow->lastY = static_cast<GLfloat>(yPos);

}
