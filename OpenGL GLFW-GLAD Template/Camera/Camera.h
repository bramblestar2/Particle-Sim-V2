#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Essentials/Vec3/Vec3.h"
#include "../Essentials/Vec2/Vec2.h"
//THIS CLASS WILL HANDLE 3D VIEWING

enum class Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera
{
public:
	Camera(const Vec2f _Size = Vec2f(), const Vec3f _Cam_Position = Vec3f());
	~Camera();

	glm::vec3 getDirection() const;
	glm::vec3 getPosition() const;
	glm::mat4* getViewPtr();
	float getSpeed() const;
	float getYaw() const;
	float getPitch() const;
	float getFOV() const;

	void enableDepth();
	void setSpeed(const float _Speed);
	void setViewDistance(const float _Near, const float _Far);
	void setPosition(const glm::vec3 _Position);
	void setSize(const Vec2f _Size);
	void setDeltaTime(const float _DT);
	void setYaw(const float _Yaw);
	void setPitch(const float _Pitch);
	void setFOV(float _FOV);

	void addPitch(const float _Pitch);
	void addYaw(const float _Yaw);
	void move(const Camera_Movement _Movement);
	void move(const glm::vec3 _Direction);

	void update(); //Updates OpenGL View matrix
private:
	void updateDirection();
	void updateView(); //Updates OpenGL glFustrum

	float dt;
	float cameraSpeed;

	Vec2f cameraSize;
	//X > Near
	//Y > Far
	Vec2f viewDistance;

	//Camera
	glm::mat4 proj;
	glm::mat4 model;
	glm::mat4 view;

	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float fov;
	//

	//
	float yaw, pitch;
	//
};