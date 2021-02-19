#include "FPS_Counter.h"

FPS_Counter::FPS_Counter()
{
	last_time = (float)glfwGetTime();
}

void FPS_Counter::count_fps()
{
	current_time = (float)glfwGetTime();
	n_frames++;

	// miliseconds per frame more relevant than frames per second
	if (current_time - last_time >= 1.0f)
	{
		std::cout << 1000.0f / n_frames << "ms / frame\n";
		n_frames = 0;
		last_time += 1.0f;
	}
}
