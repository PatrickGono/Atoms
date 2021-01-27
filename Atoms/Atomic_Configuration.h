#pragma once
#include <vector>
#include <math.h>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "CommonValues.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Atom.h"
#include "Bond.h"
#include "Shader.h"

class Atomic_Configuration
{
private:
	std::string input_file_name;
	std::vector<std::unique_ptr<Body>> bodies;
	std::vector<Atom> atoms;
	std::vector<Bond> bonds;

public:
	Atomic_Configuration(std::string & file_name);
	~Atomic_Configuration();

	void render(Shader * shader);

	void read_xyz_file();

	void create_bonds(float cutoff);
};

