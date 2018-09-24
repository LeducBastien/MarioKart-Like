#include <SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "TriangleSceneNode.h"

namespace id
{

	TriangleSceneNode::TriangleSceneNode()
	{
	}

	TriangleSceneNode::~TriangleSceneNode()
	{
		/*glDeleteBuffers(1, &this->vbo);
		glDeleteBuffers(1, &this->vao);*/

		this->triangle.clear();
	}

	TriangleSceneNode* TriangleSceneNode::create(SceneManager* scenemgr, SceneNode* parent)
	{
		TriangleSceneNode* node = new TriangleSceneNode();

                node->scenemgr = scenemgr;
                node->parent = parent;
                node->children = {};

                parent->addChild(node);

		node->setDrawSettings();

                return node;

	}

	void TriangleSceneNode::setDrawSettings()
	{
		this->triangle =
        	{
                	1.0f,0.0f, 0.f,        0.75f, 0.6f, 0.0f, 1.0f,
        	        0.0f, 1.0f, 0.f,       0.5f, 0.3f, 0.0f, 1.0f,
	                -1.0f,0.0f, 0.f,       0.75f, 0.6f, 0.0f, 1.0f,
        	};

        	glGenVertexArrays(1, &this->vao);
	        glGenBuffers(1,&this->vbo);

        	glBindVertexArray(this->vao);
	        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        	glBufferData(GL_ARRAY_BUFFER, this->triangle.size() * sizeof(this->triangle[0]), this->triangle.data(), GL_STATIC_READ);

	        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), nullptr);
        	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	        glEnableVertexAttribArray(0);
        	glEnableVertexAttribArray(1);
	        glClearColor(0.f, 0.f, 0.f ,1.f);

	}

	void TriangleSceneNode::draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);

		std::vector<SceneNode*>::iterator first = this->children.begin();
		std::vector<SceneNode*>::iterator last = this->children.end();

		for (; first != last; ++first)
			(*first)->draw();
	}

}
