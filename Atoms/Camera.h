#pragma once
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

#include "CommonValues.h"


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

	void initialize_camera_vectors();
	void update_camera_vectors(glm::mat4 & transform);

public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float pos_x = 0.0f, float pos_y = 0.0f, float pos_z = 0.0f, float up_x = 0.0f, float up_y = 0.0f, float up_z = 0.0f, float yaw = YAW, float pitch = PITCH);
	~Camera();

	glm::mat4 get_view_matrix();
	glm::vec3 get_position() { return position; }

	void process_keyboard(bool* keys, GLfloat delta_time);
	void process_mouse_movement(float x_change, float y_change);
	void process_mouse_scroll(float y_change, GLfloat delta_time);




};

