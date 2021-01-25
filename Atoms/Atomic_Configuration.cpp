#include "Atomic_Configuration.h"




Atomic_Configuration::Atomic_Configuration(std::string & file_name) : input_file(file_name)
{
	positions.push_back(glm::vec3(1.0, 0.0, 0.0));

	positions.push_back(glm::vec3(-1.0, 0.0, 0.0));

	positions.push_back(glm::vec3(0.0, 1.0, 0.0));

	positions.push_back(glm::vec3(0.0, -1.0, 0.0));

	bodies.emplace_back(std::make_unique<Sphere>(0.2f));
}

Atomic_Configuration::~Atomic_Configuration()
{
}

void Atomic_Configuration::render(Shader * shader)
{
	glm::mat4 model(1.0f);

	for (auto position : positions)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		shader->set_mat4("model", model);
		bodies[0]->render();
	}
}

void Atomic_Configuration::read_xyz_file()
{
	// TODO:

	// open file_name

	// read in positions for each atom
}

