#pragma once
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <iostream>
#include <memory>
#include "CommonValues.h"
#include "Body.h"

class Sphere :
	public Body
{
private:
	float radius;

public:
	Sphere(float radius);

	void create_mesh();
};

