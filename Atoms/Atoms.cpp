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

#include "Shader.h"
#include "Atomic_Configuration.h"
#include "Camera.h"
#include "Window.h"
#include "FPS_Counter.h"


void handle_input(Camera & camera, Window & window, float delta_time)
{
	// poll events from the window and pass mouse and keyboard input to the camera
	glfwPollEvents();
	camera.process_keyboard(window.get_keys(), delta_time);
	camera.process_mouse_movement(window.get_x_change(), window.get_y_change());
	camera.process_mouse_scroll(window.get_z_change(), delta_time);
	return;
}

void render_pass(Shader & shader, Camera & camera, Window & window, Atomic_Configuration & config)
{
	// clear scene, set background color
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use_shader();

	// set view and projection matrices
	shader.set_mat4("view", camera.get_view_matrix());
	glm::mat4 projection = glm::perspective(glm::radians(35.0f), window.get_buffer_width() / window.get_buffer_height(), 0.1f, 1000.0f);
	shader.set_mat4("projection", projection);

	// pass camera position to the shader
	glm::vec3 view_position = camera.get_position();
	shader.set_vec3("view_position", view_position.x, view_position.y, view_position.z);

	// set light color and direction
	shader.set_vec3("light_color", 1.0f, 1.0f, 1.0f);
	glm::vec3 directional_light_direction(-0.3f, -0.3f, 1.0f);
	shader.set_vec3("directional_light_direction", directional_light_direction.x, directional_light_direction.y, directional_light_direction.z);

	config.render(&shader);

	window.swap_buffers();
	return;
}

int main(int argc, char * argv[])
{
	// create window
	int screen_width{ 1200 };
	int screen_height{ 800 };
	Window window(screen_width, screen_height);
	window.initialize();

	// compile shader
	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");

	// handle input .xyz file path as command line argument
	std::string filename{ 0 };
	if (argc < 2)
		std::cout << "Supply .xyz file path as command line argument!\n";
	else
		filename = std::string(argv[1]);

	// create atomic configuration from input file
	Atomic_Configuration config(filename);

	// set up camera
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

	float now_time = glfwGetTime();
	float last_time = glfwGetTime();
	float delta_time{ 0.0f };

	FPS_Counter fps_counter;

	while (!window.get_should_close())
	{
		now_time = glfwGetTime();
		delta_time = now_time - last_time;
		last_time = now_time;
		
		fps_counter.count_fps();

		handle_input(camera, window, delta_time);

		render_pass(shader, camera, window, config);
	}

	glfwTerminate();
	return 0;

}