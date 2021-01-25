// Atoms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "CommonValues.h"
#include "Shader.h"
#include "Sphere.h"
#include "Atomic_Configuration.h"
#include "Camera.h"
#include "Window.h"

int n_frames{ 0 };
double last_time{ 0.0f };
float mix{ 0.0f };


void countFPS()
{
	double currentTime = glfwGetTime();
	n_frames++;
	if (currentTime - last_time >= 1.0)
	{
		std::cout << 1000.0 / n_frames << "ms / frame\n";
		n_frames = 0;
		last_time += 1.0;
	}
}

int main()
{
	int screen_width{ 800 };
	int screen_height{ 600 };
	Window window(screen_width, screen_height);
	window.initialize();

	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");

	last_time = glfwGetTime();


	std::string filename{ "TiO2.xyz" };
	Atomic_Configuration config(filename);

	glm::vec3 directional_light_direction(-0.3f, -0.3f, 1.0f);

	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

	while (!window.get_should_close())
	{
		//process_input(window);

		double now_time = glfwGetTime();
		double delta_time = now_time - last_time;
		last_time = now_time;
		countFPS();

		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		camera.process_keyboard(window.get_keys(), delta_time);
		camera.process_mouse_movement(window.get_x_change(), window.get_y_change());
		camera.process_mouse_scroll(window.get_z_change(), delta_time);
		// TODO: figure out mouse scrolling
		//camera.process_mouse_scroll()

		shader.use_shader();

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)screen_width / screen_height, 0.1f, 100.0f);

		float angle = (float)glfwGetTime();


		shader.set_mat4("view", camera.get_view_matrix());
		shader.set_mat4("projection", projection);
		shader.set_vec3("light_color", 1.0f, 1.0f, 1.0f);
		shader.set_vec3("object_color", 1.0f, 0.5f, 0.31f);
		glm::vec3 view_position = camera.get_position();
		shader.set_vec3("view_position", view_position.x, view_position.y, view_position.z);
		directional_light_direction = glm::vec3(1.0f - std::sin(angle), 0.0, 1.0f - std::cos(angle));
		shader.set_vec3("directional_light_direction", directional_light_direction.x, directional_light_direction.y, directional_light_direction.z);


		glm::mat4 model(1.0f);

		config.render(&shader);

		window.swap_buffers();
	}

	glfwTerminate();
	return 0;

}