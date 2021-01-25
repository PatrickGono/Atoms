#pragma once
#include <vector>
#include <math.h>
#include <string>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <memory>
#include "Atom.h"
#include "CommonValues.h"
#include "Sphere.h"
#include "Shader.h"

class Atomic_Configuration
{
private:
	std::string input_file;
	std::vector<glm::vec3> positions;
	std::vector<std::unique_ptr<Body>> bodies;

public:
	Atomic_Configuration(std::string & file_name);
	~Atomic_Configuration();

	void render(Shader * shader);

	void read_xyz_file();
};

