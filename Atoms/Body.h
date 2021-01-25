#pragma once
#include "Mesh.h"
#include <GLM/glm.hpp>

class Body
{
protected:
	std::unique_ptr<Mesh> mesh;

public:
	Body();
	~Body();

	virtual void create_mesh() = 0;
	void render();
};

