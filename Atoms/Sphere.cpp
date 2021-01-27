#include "Sphere.h"

Sphere::Sphere()
{
	create_mesh();
}

void Sphere::create_mesh()
{
	unsigned int n_stacks = 18;
	unsigned int n_sectors = 36;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	float x, y, z, nx, ny, nz;
	float radius = 0.25f;
	float inv_radius = 1.0f / radius;
	float stack_angle, sector_angle;

	unsigned int n_vertices = 0;
	unsigned int n_indices = 0;

	for (unsigned int stack = 0; stack <= n_stacks; ++stack)
	{
		stack_angle = stack / (float)n_stacks * PI;
		for (unsigned int sector = 0; sector <= n_sectors; ++sector)
		{
			sector_angle = sector / (float)n_sectors * 2 * PI;
			x = radius * cos(sector_angle) * sin(stack_angle);
			y = radius * sin(sector_angle) * sin(stack_angle);
			z = radius * cos(stack_angle);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			nx = x * inv_radius;
			ny = y * inv_radius;
			nz = z * inv_radius;
			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);

			n_vertices++;
		}
	}

	unsigned int k1, k2;
	for (unsigned int stack = 0; stack < n_stacks; ++stack)
	{
		k1 = stack * (n_sectors + 1);
		k2 = (stack + 1) * (n_sectors + 1);

		for (unsigned int sector = 0; sector < n_sectors; ++sector, ++k1, ++k2)
		{
			if (stack != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
				n_indices = n_indices + 3;
			}

			if (stack != n_stacks - 1)
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
				n_indices = n_indices + 3;
			}
		}
	}


	mesh = std::make_unique<Mesh>();
	mesh->create_mesh(vertices.data(), indices.data(), n_vertices, n_indices);
}
