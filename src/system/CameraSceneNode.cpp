#include <iostream>

#include "maths/tools.h"

#include "PollEvent.h"
#include "Driver.h"
#include "SceneManager.h"
#include "CameraSceneNode.h"

namespace id
{

	CameraSceneNode::CameraSceneNode()
	: SceneNode()
	{
	}

	CameraSceneNode::~CameraSceneNode()
	{
	}

	auto CameraSceneNode::create(Driver* drv, SceneManager* scenemgr, SceneNode* parent) -> CameraSceneNode*
	{
		auto* cam = new CameraSceneNode();
		GLuint prg_id = drv->getCurrentProgram();

		cam->driver = scenemgr->getDriver();
		cam->scenemgr = scenemgr;
		cam->parent = parent;

		if (parent)
			parent->addChild(cam);

		cam->view_loc = glGetUniformLocation(prg_id, "view");
                cam->proj_loc = glGetUniformLocation(prg_id, "proj");

		cam->view = maths::Matrix4::translate(cam->posX, cam->posY, cam->posZ).inverse();
                cam->proj = maths::Matrix4::perspective(deg2rad(90.f), 1.f, 0.1f, 1000.f);

		return cam;
	}

	void CameraSceneNode::switchShader()
	{
		GLuint prg_id = this->driver->getCurrentProgram();

		GLuint vao = this->driver->getVAO();
                glBindVertexArray(vao);

		this->view_loc = glGetUniformLocation(prg_id, "view");
                this->proj_loc = glGetUniformLocation(prg_id, "proj");

		this->view = maths::Matrix4::translate(this->posX, this->posY, this->posZ).inverse() * maths::Matrix4x4::rotateY(this->angleX) * maths::Matrix4x4::rotateX(this->angleY);
		this->proj = maths::Matrix4::perspective(deg2rad(90.f), 1.f, 0.1f, 1000.f);

		glUniformMatrix4fv(this->view_loc, 1, GL_TRUE, this->view.val);
                glUniformMatrix4fv(this->proj_loc, 1, GL_TRUE, this->proj.val);

		glBindVertexArray(0);
	}

	void CameraSceneNode::draw()
	{
		this->event();

		this->switchShader();

	}

	void CameraSceneNode::event()
	{
		if (!SceneNode::is_typing_text)
		{
			this->mouseEvent();
			this->keyboardEvent();
		}
	}

	void CameraSceneNode::mouseEvent()
	{
		/*int rel_x = PollEvent::getMouseRelX();
		int rel_y = PollEvent::getMouseRelY();

		this->angleX += rel_x;
		this->angleY += rel_y;*/
	}

	void CameraSceneNode::keyboardEvent()
	{
		SDL_Scancode key = PollEvent::getKeyInput();

                switch(key)
                {
                        case SDL_SCANCODE_LEFT:
                                --(this->posX);
                        break;

                        case SDL_SCANCODE_RIGHT:
                                ++(this->posX);
                        break;

                        case SDL_SCANCODE_W:
                                --(this->posZ);
                        break;

                        case SDL_SCANCODE_S:
                                ++(this->posZ);
                        break;

                        case SDL_SCANCODE_A:
                                --(this->angleX);
                        break;

                        case SDL_SCANCODE_D:
                                ++(this->angleX);
                        break;

			case SDL_SCANCODE_Z:
				--(this->angleY);
			break;

			case SDL_SCANCODE_X:
				++(this->angleY);
			break;

			case SDL_SCANCODE_UP:
                                ++(this->posY);
                        break;

                        case SDL_SCANCODE_DOWN:
                                --(this->posY);
                        break;

                        default: break;
                }
	}
}
