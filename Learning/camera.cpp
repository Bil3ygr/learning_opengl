#include "camera.h"

void Camera::mouseMove(float xoffset, float yoffset, GLboolean limit)
{
	if (!_enable)
		return;

	xoffset *= _sensitivity;
	yoffset *= _sensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (limit)
	{
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		else if (_pitch < -89.0f)
			_pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::keyMove(Camera_Movement dir, float time)
{
	if (!_enable)
		return;

	float velocity = _speed * time;
	if (dir == Camera_Movement::FORWARD)
		pos += front * velocity;
	else if (dir == Camera_Movement::BACKWARD)
		pos -= front * velocity;
	else if (dir == Camera_Movement::LEFT)
		pos -= right * velocity;
	else if (dir == Camera_Movement::RIGHT)
		pos += right * velocity;
}

void Camera::mouseScroll(float yoffset)
{
	if (!_enable)
		return;

	if (_zoom >= 1.0f && _zoom <= 45.0f)
		_zoom -= yoffset;
	if (_zoom <= 1.0f)
		_zoom = 1.0f;
	if (_zoom >= 45.0f)
		_zoom = 45.0f;
}

void Camera::setSensitivity(float sensitivity)
{
	_sensitivity = sensitivity;
}

void Camera::setSpeed(float speed)
{
	_speed = speed;
}

void Camera::setEnable(bool enable)
{
	_enable = enable;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(pos, pos + front, realUp);
}

glm::mat4 Camera::getProjection()
{
	return glm::perspective(glm::radians(_zoom), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::updateCameraVectors()
{
	glm::vec3 _front = glm::vec3(1.0f);
	_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front.y = sin(glm::radians(_pitch));
	_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front = glm::normalize(_front);

	right = glm::normalize(glm::cross(front, up));
	realUp = glm::normalize(glm::cross(right, front));
}