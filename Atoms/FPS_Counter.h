#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class FPS_Counter
{
private:
	float current_time{ 0.0f };
	float last_time{ 0.0f };
	unsigned int n_frames{ 0 };

public:
	FPS_Counter();

	void count_fps();
};

