#ifndef __MESH_H_INCLUDED__
#define __MESH_H_INCLUDED__

#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include "Log.h"

namespace id
{

class Mesh
{
public:
	Mesh(Mesh const&) = delete;
	Mesh(Mesh&&) = delete;
	virtual ~Mesh();

	auto operator=(Mesh const&) -> Mesh& = delete;
	auto operator=(Mesh&&) -> Mesh& = delete;

	std::vector<GLfloat> getPoints() {return this->points;}

	int getPointNumber() const {return nb_points;}
	static Mesh* create();

	virtual void draw();

	bool getMeshState() const {return model_only;}
	void setMeshState(bool state) {model_only = state;}
	
protected:
	Mesh();

	id::log::Log log;

	std::vector<GLfloat> points;
	unsigned int nb_points = 0;

	bool model_only = false;

};

}

#endif
