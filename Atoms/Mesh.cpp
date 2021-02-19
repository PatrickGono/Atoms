#include "Mesh.h"

Mesh::Mesh()
{
	VBO = 0;
	VAO = 0;
	IBO = 0;
	index_count = 0;
}

Mesh::~Mesh()
{
	clear_mesh();
}


void Mesh::create_mesh(GLfloat * vertices, unsigned int * indices, unsigned int n_vertices, unsigned int n_indices)
{
	index_count = n_indices;

	// create one vertex array and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// create one element buffer, bind it, and attach the data of the indices
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * n_indices, indices, GL_STATIC_DRAW);

	// create one vertex buffer, bind it, and attach the data
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * n_vertices * 6, vertices, GL_STATIC_DRAW);

	// position vectors (attribute 0), there are three coordinates, we need to read 
	// them with a stride of 6 as there are also the normals, and use 0 offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, 0);
	glEnableVertexAttribArray(0);

	// normal vectors (attribute 1), there are three coordinates, stride 6, offset 3
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::render_mesh()
{
	// bind vertex aray and element buffer, render triangles, then unbind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Mesh::clear_mesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}
