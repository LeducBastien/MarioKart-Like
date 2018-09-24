#ifndef __MANUALMESH_H_INCLUDED__
#define __MANUALMESH_H_INCLUDED__

#include "Mesh.h"

namespace id
{

class ManualMesh
: public Mesh
{
public:
	ManualMesh(ManualMesh const&) = delete;
	ManualMesh(ManualMesh&&) = delete;
	virtual ~ManualMesh() = default;

	auto operator=(ManualMesh const&) -> ManualMesh& = delete;
	auto operator=(ManualMesh&&) -> ManualMesh& = delete;

	static ManualMesh* create();

	void addPoint(float x,float y,float z,float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
	void setMesh(std::vector<GLfloat>);

	

private:
	ManualMesh();
};

}

#endif
