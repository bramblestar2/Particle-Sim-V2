#include "Camera.h"
#include <iostream>

Camera::Camera(const Vec2f _Size, const Vec3f _Cam_Position)
{
	cameraSize = _Size;
	setSpeed(0.5f);
	setViewDistance(1, 500);

	yaw = 0;
	pitch = 0;
	fov = 45;

	model = glm::mat4(1.f);
	proj = glm::mat4(1.f);
	view = glm::mat4(1.f);

	cameraPos = glm::vec3(_Cam_Position.x, _Cam_Position.y, _Cam_Position.z);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);

	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	setDeltaTime(1);

	updateDirection();
	updateView();
}

Camera::~Camera()
{
}

glm::vec3 Camera::getDirection() const
{
	return cameraFront;
}

float Camera::getSpeed() const
{
	return cameraSpeed;
}

glm::vec3 Camera::getPosition() const
{
	return cameraPos;
}

float Camera::getYaw() const
{
	return yaw;
}

float Camera::getPitch() const
{
	return pitch;
}

glm::mat4* Camera::getViewPtr()
{
	return &view;
}

float Camera::getFOV() const
{
	return fov;
}

void Camera::enableDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void Camera::setSpeed(const float _Speed)
{
	cameraSpeed = _Speed;
}

void Camera::setViewDistance(const float _Near, const float _Far)
{
	viewDistance = Vec2f(_Near, _Far);
}

void Camera::setPosition(const glm::vec3 _Position)
{
	cameraPos = _Position;
}

void Camera::setSize(const Vec2f _Size)
{
	cameraSize = _Size;
	updateView();
}

void Camera::setDeltaTime(const float _DT)
{
	dt = _DT;
}

void Camera::setYaw(const float _Yaw)
{
	yaw = _Yaw;
	updateDirection();
}

void Camera::setPitch(const float _Pitch)
{
	pitch = _Pitch;
	updateDirection();
}

void Camera::setFOV(float _FOV)
{
	fov = _FOV;
}

void Camera::addPitch(const float _Pitch)
{
	pitch += _Pitch;
	updateDirection();
}

void Camera::addYaw(const float _Yaw)
{
	yaw += _Yaw;
	updateDirection();
}

void Camera::move(const Camera_Movement _Movement)
{
	float camSpeed = cameraSpeed * dt;

	switch (_Movement)
	{
	case Camera_Movement::FORWARD:
		cameraPos.x += camSpeed * cos(glm::radians(yaw));
		cameraPos.z += camSpeed * sin(glm::radians(yaw));
		//cameraPos += camSpeed * cameraFront;

		break;
	case Camera_Movement::BACKWARD:
		cameraPos.x -= camSpeed * cos(glm::radians(yaw));
		cameraPos.z -= camSpeed * sin(glm::radians(yaw));
		//cameraPos -= camSpeed * cameraFront;
		break;
	case Camera_Movement::LEFT:
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
		break;
	case Camera_Movement::RIGHT:
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
		break;
	case Camera_Movement::UP:
		cameraPos.y += camSpeed;
		break;
	case Camera_Movement::DOWN:
		cameraPos.y -= camSpeed;
		break;
	}
}

void Camera::move(const glm::vec3 _Direction)
{
	cameraPos += _Direction;
}

void Camera::update()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(glm::value_ptr(view));
}

void Camera::updateDirection()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void Camera::updateView()
{
	glViewport(0.0f, 0.0f, cameraSize.x, cameraSize.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)cameraSize.x / (float)cameraSize.y;
	glFrustum(-ratio, ratio, -1.f, 1.f, viewDistance.x, viewDistance.y);
}
