#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

#include "Mesh.h"

namespace id
{
	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
		this->points.clear();
	}

	Mesh* Mesh::create()
	{
		auto* mesh = new Mesh();

		mesh->log.setIdentifier("Mesh");
		mesh->log.setOutput(id::log::BOTH);

		return mesh;
	}

	void Mesh::draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, this->nb_points);
	}
}
