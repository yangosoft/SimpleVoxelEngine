#include "CameraController.hpp"

CameraController::CameraController(GLFWwindow* window,
	float mouseSpeed,
	float keyboardSpeed) : _window(window), _mouseSpeed(mouseSpeed), _keyboardSpeed(keyboardSpeed), _firstUpdate(true), _windowWidth(0), _windowHeight(0)
{
}


CameraController::~CameraController()
{
	
}

void CameraController::update(float timeDelta)
{
	int windowWidth = 0, windowHeight = 0;
	if (windowWidth == 0)
	{
		glfwGetWindowSize(_window, &windowWidth, &windowHeight);
	}

	double xpos, ypos;
	if (!_firstUpdate)
	{
		glfwGetCursorPos(_window, &xpos, &ypos);
	}
	else
	{
		xpos = windowWidth / 2;
		ypos = windowHeight / 2;
		_firstUpdate = false;
	}

	glfwSetCursorPos(_window, windowWidth / 2, windowHeight / 2);
	_leftThumbStickDelta = controllerDelta(_mouseSpeed * float(windowWidth / 2 - xpos), _mouseSpeed * float(windowHeight / 2 - ypos));

	float rightX = 0, rightY = 0;
	if ((glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) || (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS))
	{
		rightY = _keyboardSpeed * timeDelta;
	}else if ((glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) || (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS))
	{
		rightY = -_keyboardSpeed * timeDelta;
	}else if ((glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) || (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS))
	{
		rightX = _keyboardSpeed * timeDelta;
	}else if ((glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) || (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS))
	{
		rightX = -_keyboardSpeed * timeDelta;
	}else if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		rightY = -_keyboardSpeed * timeDelta;
	}
	_rightThumbStickDelta = controllerDelta(rightX, rightY);
}

