#pragma once
#include <string>
#include <map>
#include <GLM/glm.hpp>

struct Atom
{
	float radius;
	glm::vec3 color;
	glm::vec3 position;
	std::string element;
};

extern std::map<std::string, glm::vec3> ATOM_COLOR_DICT;
extern std::map<std::string, float> ATOM_RADIUS_DICT;
