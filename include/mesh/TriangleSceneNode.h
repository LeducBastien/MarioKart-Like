#ifndef __TRIANGLESCENENODE_H_INCLUDED__
#define __TRIANGLESCENENODE_H_INCLUDED__

#include <memory>
#include <vector>
#include <SDL.h>
#include <GL/glew.h>

#include "SceneNode.h"

namespace id
{

	class SceneManager;

	class TriangleSceneNode
	: public SceneNode
	{
	public:
		TriangleSceneNode(TriangleSceneNode const&) = delete;
		TriangleSceneNode(TriangleSceneNode&&) = delete;
		virtual ~TriangleSceneNode();

		auto operator=(TriangleSceneNode const&) -> TriangleSceneNode& = delete;
		auto operator=(TriangleSceneNode&&) -> TriangleSceneNode& = delete;

		static TriangleSceneNode* create(SceneManager*, SceneNode*);
		void setDrawSettings();

		virtual void draw();

	private:
		TriangleSceneNode();

		std::vector<GLfloat> triangle;
		unsigned int nb_points = 0;

		GLuint vbo;
		GLuint vao;
	};

}

#endif
