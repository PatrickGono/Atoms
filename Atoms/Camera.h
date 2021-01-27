#pragma once
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>


enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;
	glm::vec3 front;

	float yaw;
	float pitch;

	float movement_speed;
	float mouse_sensitivity;
	float zoom;

	void update_camera_vectors();

public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float upX = 0.0f, float upY = 0.0f, float upZ = 0.0f, float yaw = YAW, float pitch = PITCH);
	~Camera();

	glm::mat4 get_view_matrix();
	glm::vec3 get_position() { return position; }

	void process_keyboard(bool* keys, GLfloat deltaTime);
	void process_mouse_movement(float xOffset, float yOffset);
	void process_mouse_scroll(float yOffset, GLfloat deltaTime);




};

