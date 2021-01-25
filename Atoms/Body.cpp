#include "Body.h"

Body::Body() : mesh( nullptr )
{
}

Body::~Body()
{
}

void Body::render()
{
	if (!mesh)
	{
		return;
	}

	mesh->render_mesh();
}
