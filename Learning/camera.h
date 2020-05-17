#pragma once
#include "main.h"
#include "globals.h"


#ifndef _CAMERA_H

class Camera
{
public:
	glm::vec3 pos = glm::vec3(0, 0, 3.0f);
	glm::vec3 front = glm::vec3(0, 0, -1.0f);
	glm::vec3 up = glm::vec3(0, 1.0f, 0);
	glm::vec3 right, realUp;

	Camera() 
	{
		updateCameraVectors();
	}
	Camera(glm::vec3 _pos, glm::vec3 _front, glm::vec3 _up) :pos(_pos), front(_front), up(_up) 
	{
		updateCameraVectors();
	}

	void mouseMove(float xoffset, float yoffset, GLboolean limit = true);
	void keyMove(Camera_Movement dir, float time);
	void mouseScroll(float yoffset);
	void setSensitivity(float sensitivity);
	void setSpeed(float speed);
	void setEnable(bool enable);
	glm::mat4 getView();
	glm::mat4 getProjection();

private:
	bool _enable = false;
	double _x, _y;
	float _yaw = -90.f, _pitch = 0;
	float _sensitivity = 0.1f, _speed = 2.5f, _zoom = 45.0f;

	void updateCameraVectors();
};

#endif // !_CAMERA_H
