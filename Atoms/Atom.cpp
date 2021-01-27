#include "Atom.h"

std::map<std::string, glm::vec3> ATOM_COLOR_DICT = {
	{ "H",  {1.00f, 1.00f, 1.00f}},
	{ "Ti", {0.65f, 0.60f, 0.90f}},
	{ "O",  {1.00f, 0.00f, 0.00f}},
	{ "C",  {0.30f, 0.30f, 0.30f}},
	{ "N",  {0.30f, 0.30f, 1.00f}}
};

std::map<std::string, float> ATOM_RADIUS_DICT = {
	{ "H",  0.2f },
	{ "Ti", 0.4f },
	{ "C",  0.4f },
	{ "O",  0.4f },
	{ "N",  0.4f }
};
