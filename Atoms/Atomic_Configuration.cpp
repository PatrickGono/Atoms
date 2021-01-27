#include "Atomic_Configuration.h"




Atomic_Configuration::Atomic_Configuration(std::string & file_name) : input_file_name(file_name)
{
	bodies.emplace_back(std::make_unique<Sphere>());
	bodies.emplace_back(std::make_unique<Cylinder>());
	read_xyz_file();
	create_bonds(2.0f);
}

Atomic_Configuration::~Atomic_Configuration()
{
}

void Atomic_Configuration::render(Shader * shader)
{
	glm::mat4 model(1.0f);

	// render atoms
	for (auto atom : atoms)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, atom.position);
		model = glm::scale(model, glm::vec3(atom.radius));
		shader->set_mat4("model", model);
		shader->set_vec3("object_color", atom.color.x, atom.color.y, atom.color.z);
		bodies[0]->render();
	}

	// render bonds
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	for (auto bond : bonds)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, bond.position);
		glm::vec3 axis = glm::cross(bond.orientation, up);
		float angle = (glm::dot(bond.orientation, up) + 1.0f) * 0.5f * PI;
		model = glm::rotate(model, angle, axis);
		model = glm::scale(model, glm::vec3(bond.radius, bond.radius, bond.height));

		shader->set_mat4("model", model);
		shader->set_vec3("object_color", bond.color.x, bond.color.y, bond.color.z);
		bodies[1]->render();
	}
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


void Atomic_Configuration::create_bonds(float cutoff)
{
	for (auto atom1 : atoms)
	{
		for (auto atom2 : atoms)
		{
			glm::vec3 diff = atom2.position - atom1.position;
			float distance = glm::dot(diff, diff);

			// no bond between hydrogen atoms
			if (atom1.element == "H" && atom2.element == "H")
				continue;

			if (distance > 0.01f && distance <= cutoff)
			{
				glm::vec3 position = atom1.position + 0.25f * diff;
				glm::vec3 orientation = glm::normalize(diff);
				float height = 0.505f * distance;
				Bond bond{ 0.10f, height, atom1.color, position, orientation };

				bonds.push_back(bond);
			}
		}
	}
}

