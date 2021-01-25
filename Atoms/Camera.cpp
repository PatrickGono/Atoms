#include "Camera.h"





Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
	: movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM),
	  yaw(yaw), pitch(pitch), position(pos), front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	world_up = up;
	update_camera_vectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
	: movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM),
	  yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	position = glm::vec3(pos_x, pos_y, pos_z);
	world_up = glm::vec3(up_x, up_y, up_z);
	update_camera_vectors();
}

Camera::~Camera()
{
}


void Camera::process_keyboard(bool* keys, GLfloat delta_time)
{
	GLfloat velocity = movement_speed * delta_time;

	if (keys[GLFW_KEY_W])
		position += velocity * front;
	if (keys[GLFW_KEY_S])
		position -= velocity * front;
	if (keys[GLFW_KEY_D])
		position += velocity * right;
	if (keys[GLFW_KEY_A])
		position -= velocity * right;
}

void Camera::process_mouse_movement(float x_change, float y_change)
{
	x_change *= mouse_sensitivity;
	y_change *= mouse_sensitivity;

	yaw += x_change;
	pitch += y_change;

	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	update_camera_vectors();	
}

void Camera::process_mouse_scroll(float z_change, GLfloat delta_time)
{
	GLfloat velocity = movement_speed * delta_time;
	zoom = z_change * velocity * 0.1;
	//std::cout << zoom << "\n";
	//position += zoom * front;
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update_camera_vectors()
{
	glm::vec3 new_front;
	new_front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	new_front.y = std::sin(glm::radians(pitch));
	new_front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front = glm::normalize(new_front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}