#include "Cylinder.h"

Cylinder::Cylinder()
{
	create_mesh();
}

void Cylinder::create_mesh()
{
	unsigned int n_sectors = 36;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	float x, y, z, nx, ny, nz;
	float radius = 1.0f;
	float height = 1.0f;
	float inv_radius = 1.0f / radius;
	float sector_angle;

	unsigned int n_vertices = 0;
	unsigned int n_indices = 0;

	for (unsigned int sector = 0; sector <= n_sectors; ++sector)
	{
		sector_angle = sector / (float)n_sectors * 2 * PI;

		// bottom edge
		x = radius * cos(sector_angle);
		y = radius * sin(sector_angle);
		z = -0.5f * height;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);

		nx = x * inv_radius;
		ny = y * inv_radius;
		nz = 0.0f;

		vertices.push_back(nx);
		vertices.push_back(ny);
		vertices.push_back(nz);

		n_vertices++;

		// top edge
		z = 0.5f * height;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);

		vertices.push_back(nx);
		vertices.push_back(ny);
		vertices.push_back(nz);

		n_vertices++;
	}

	unsigned int k;
	for (unsigned int sector = 0; sector < n_sectors; ++sector)
	{
		k = 2 * sector;

		indices.push_back(k);
		indices.push_back(k + 1);
		indices.push_back(k + 2);
		n_indices = n_indices + 3;

		indices.push_back(k + 2);
		indices.push_back(k + 1);
		indices.push_back(k + 3);
		n_indices = n_indices + 3;
	}

	mesh = std::make_unique<Mesh>();
	mesh->create_mesh(vertices.data(), indices.data(), n_vertices, n_indices);
}
