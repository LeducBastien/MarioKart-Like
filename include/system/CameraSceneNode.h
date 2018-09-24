#ifndef __CAMERASCENENODE_H_INCLUDED__
#define __CAMERASCENENODE_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>

#include "maths/Matrix.h"
#include "SceneNode.h"

namespace id
{
	class Driver;
	class SceneManager;

	class CameraSceneNode
	: public SceneNode
	{
	public:
		CameraSceneNode(CameraSceneNode const&) = delete;
		CameraSceneNode(CameraSceneNode&&) = delete;
		virtual ~CameraSceneNode();

		auto operator=(CameraSceneNode const&) -> CameraSceneNode& = delete;
		auto operator=(CameraSceneNode&&) -> CameraSceneNode& = delete;

		static auto create(Driver*,SceneManager*,SceneNode*) -> CameraSceneNode*;

		void switchShader();

		virtual void draw();
		virtual void event();

		void mouseEvent();
		virtual void keyboardEvent();

	private:
		CameraSceneNode();

		GLint view_loc;
		GLint proj_loc;

		maths::Matrix4 view;
		maths::Matrix4 proj;

		float angleX = 0.f;
		float angleY = 0.f;
		float posX = 0.f;
		float posY = 0.f;
		float posZ = 70.f;
	};
}

#endif
