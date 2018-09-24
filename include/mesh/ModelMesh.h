#ifndef __MODELMESH_H_INCLUDED__
#define __MODELMESH_H_INCLUDED__

#include <string>
#include <vector>
#include <SDL.h>
#include <GL/glew.h>

#include "Mesh.h"

namespace id
{
struct Model_v
{
        GLfloat x;
        GLfloat y;
        GLfloat z;
};

struct Model_vt
{
        GLfloat x;
        GLfloat y;
};

struct Model_f
{
        unsigned int v1;
        unsigned int v2;
        unsigned int v3;

        unsigned int vt1;
        unsigned int vt2;
        unsigned int vt3;
};


	class ModelMesh
	: public Mesh
	{
	public:
		ModelMesh(ModelMesh const&) = delete;
		ModelMesh(ModelMesh&&) = delete;

		virtual ~ModelMesh();

		auto operator=(ModelMesh const&) -> ModelMesh& = delete;
		auto operator=(ModelMesh&&) -> ModelMesh& = delete;

		auto getDrawCoord() -> std::vector<GLfloat> {return this->draw_coord;}
		auto getModel() -> std::string {return this->filename;}
		auto getTexture() -> std::string {return this->texture;}

		static auto create(std::string const&, std::string const&) -> ModelMesh*;
		void loadModel();
		void setTexture();
		void getCoordinates(std::string const&);
		void getVVT(std::string const&);
		void getF(std::string const&);

		void setGLPointers();
		void addVertexCoord(Model_f mf);
		void addPoint(Model_v const&, Model_vt const&);

		virtual void draw();
	private:
		ModelMesh();

		std::string filename;
		std::string texture;

		std::vector<Model_v> mv;
		std::vector<Model_vt> mvt;
		std::vector<Model_f> mf;

		std::vector<GLfloat> draw_coord;

		GLuint tex_id = 0;
	};
}

#endif
