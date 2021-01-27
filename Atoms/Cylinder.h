#pragma once
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <iostream>
#include <memory>
#include "CommonValues.h"
#include "Body.h"

class Cylinder :
	public Body
{
private:

public:
	Cylinder();

	void create_mesh();
};

