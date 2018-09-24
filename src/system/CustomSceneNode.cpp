#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <imgui.h>

#include "Driver.h"
#include "ManualMesh.h"
#include "SceneManager.h"
#include "CustomSceneNode.h"

namespace id
{
	CustomSceneNode::CustomSceneNode()
	: SceneNode()
	{
		this->mesh = nullptr;
	}

	CustomSceneNode::~CustomSceneNode()
	{
		if (this->mesh)
		{
			delete this->mesh;
			this->mesh = nullptr;
		}
	}

	auto CustomSceneNode::create(SceneManager* scenemgr, SceneNode* parent) -> CustomSceneNode*
	{
		auto node = new CustomSceneNode();

		node->driver = scenemgr->getDriver();
		node->scenemgr = scenemgr;
		node->parent = parent;
		node->children = {};


		if (parent)
			parent->addChild(node);

		return node;
	}

	auto CustomSceneNode::createManualMesh() -> ManualMesh*
	{
		this->mesh = ManualMesh::create();

		return this->mesh;
	}

	void CustomSceneNode::setMesh(std::vector<GLfloat> mesh)
	{
		if(!this->mesh)
			this->mesh = ManualMesh::create();

		
		this->prg_id = this->driver->addShader("triforce");

		this->world_loc = glGetUniformLocation(this->prg_id, "world");
                this->world = maths::Matrix4::identity;

		this->mesh->setMesh(mesh);

                glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(mesh[0]), mesh.data(), GL_STATIC_READ);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), nullptr);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glClearColor(0.f, 0.f, 0.f ,1.f);

	}

	void CustomSceneNode::updateBuffer()
	{

		std::vector<GLfloat> mesh = this->mesh->getPoints();

		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(mesh[0]), mesh.data(), GL_STATIC_READ);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), nullptr);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glClearColor(0.f, 0.f, 0.f ,1.f);

	}

	void CustomSceneNode::updateGUIWindow()
        {
                ImGui::SetNextWindowSize(ImVec2(300,100), ImGuiSetCond_FirstUseEver);
                ImGui::Begin("Edit Triforce");
                ImGui::Text("Insert text here");
                ImGui::End();
        }


	void CustomSceneNode::draw()
	{
		this->driver->useProgram(this->prg_id, this->scenemgr);

		this->bindBufferAndVertexArrays();

		this->updateBuffer();

		this->updateWorld();

		if(this->mesh)
			this->mesh->draw();

		this->unbindBufferAndVertexArrays();

		this->updateGUIWindow();

		std::vector<SceneNode*>::iterator first = this->children.begin();
                std::vector<SceneNode*>::iterator last = this->children.end();

                for (; first != last; ++first)
                        (*first)->draw();
	}

	void CustomSceneNode::updateWorld()
	{
		this->world = maths::Matrix4::identity;

                if(this->parent)
                {
                        maths::Matrix4 parent_world = this->parent->getWorld();
                        this->world = parent_world;
                }

                this->world *= maths::Matrix4x4::rotateY(this->angle);
                this->angle += 1.5f;
                glUniformMatrix4fv(this->world_loc, 1, GL_TRUE, this->world.val);
	}
}
