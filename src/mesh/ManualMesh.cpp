#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "ManualMesh.h"

namespace id
{
	ManualMesh::ManualMesh()
	: Mesh()
	{
	}

	ManualMesh* ManualMesh::create()
	{
		auto* mesh = new ManualMesh();

		return mesh;
	}

	void ManualMesh::setMesh(std::vector<GLfloat> mesh)
        {
                this->points.clear();
                this->points = mesh;

		this->nb_points = this->points.size() / 7;
        }

        void ManualMesh::addPoint(float x, float y, float z, float r, float g, float b, float a)
        {
                this->points.push_back(x);
                this->points.push_back(y);
                this->points.push_back(z);
                this->points.push_back(r);
                this->points.push_back(g);
                this->points.push_back(b);
                this->points.push_back(a);

                ++(this->nb_points);
        }
}
