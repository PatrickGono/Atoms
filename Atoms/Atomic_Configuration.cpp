#include "Atomic_Configuration.h"




Atomic_Configuration::Atomic_Configuration(std::string & file_name) : input_file_name(file_name)
{
	bodies.emplace_back(std::make_unique<Sphere>());
	bodies.emplace_back(std::make_unique<Cylinder>());
	read_xyz_file();
}

Atomic_Configuration::~Atomic_Configuration()
{
}

void Atomic_Configuration::render(Shader * shader)
{
	glm::mat4 model(1.0f);

	// handle atoms
	for (auto atom : atoms)
	{
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(atom.radius));
		model = glm::translate(model, atom.position);
		shader->set_mat4("model", model);
		shader->set_vec3("object_color", atom.color.x, atom.color.y, atom.color.z);
		bodies[0]->render();
	}

	// handle bonds
	// TODO
}

void Atomic_Configuration::read_xyz_file()
{
	std::ifstream input_file;
	input_file.open(input_file_name, std::ios::in);

	if (!input_file.is_open())
	{
		std::cout << input_file_name << " file not found!\n";
		return;
	}

	std::string line;
	unsigned int n_atoms{ 0 };

	// read first line containing number of atoms
	std::getline(input_file, line);
	n_atoms = std::stoi(line);

	// skip comment line
	std::getline(input_file, line);

	// read rest of file
	std::string atom_type;
	float pos_x, pos_y, pos_z;

	while (std::getline(input_file, line))
	{
		std::istringstream iss(line);
		std::string element;

		iss >> element;
		iss >> pos_x;
		iss >> pos_y;
		iss >> pos_z;


		float radius = ATOM_RADIUS_DICT[element];
		glm::vec3 color = ATOM_COLOR_DICT[element];
		glm::vec3 position = glm::vec3(pos_x, pos_y, pos_z);

		Atom atom{ radius, color, position, element };

		atoms.push_back(atom);
	}

	input_file.close();
}

