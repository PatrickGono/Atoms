#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
	: movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM),
	  yaw(yaw), pitch(pitch), position(pos), front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	world_up = up;
	initialize_camera_vectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
	: movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM),
	  yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	position = glm::vec3(pos_x, pos_y, pos_z);
	world_up = glm::vec3(up_x, up_y, up_z);
	initialize_camera_vectors();
}

Camera::~Camera()
{
}

void Camera::initialize_camera_vectors()
{
	glm::vec3 new_front;
	new_front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	new_front.y = std::sin(glm::radians(pitch));
	new_front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front = glm::normalize(new_front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}


void Camera::process_keyboard(bool* keys, GLfloat delta_time)
{
	GLfloat velocity = movement_speed * delta_time;

	if (keys[GLFW_KEY_W])
		position += velocity * up;
	if (keys[GLFW_KEY_S])
		position -= velocity * up;
	if (keys[GLFW_KEY_D])
		position += velocity * right;
	if (keys[GLFW_KEY_A])
		position -= velocity * right;
}

void Camera::process_mouse_scroll(float z_change, GLfloat delta_time)
{
	zoom = z_change * 0.5 * movement_speed;
	position += zoom * front;
}

void Camera::process_mouse_movement(float x_change, float y_change)
{
	x_change *= mouse_sensitivity;
	y_change *= mouse_sensitivity;

	float angle = glm::sqrt(x_change * x_change + y_change * y_change);

	// angle is the absolute value of the rotation angle, the direction is determined by the orientation of the rotation axis
	if (angle > 0.0f)
	{
		glm::mat4 transformation = glm::mat4(1.0);
		glm::vec3 axis = glm::normalize(x_change * up + y_change * right);
		transformation = glm::rotate(transformation, angle, axis);

		update_camera_vectors(transformation);
	}
}

void Camera::update_camera_vectors(glm::mat4 & transform)
{
	glm::vec4 new_front = glm::vec4(front, 1.0f);
	new_front = transform * new_front;
	front = glm::vec3(new_front);
	front = glm::normalize(front);

	glm::vec4 new_right = glm::vec4(right, 1.0f);
	new_right = transform * new_right;
	right = glm::vec3(new_right);
	right = glm::normalize(right);

	glm::vec4 new_position = glm::vec4(position, 1.0f);
	new_position = transform * new_position;
	position = glm::vec3(new_position);

	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}
