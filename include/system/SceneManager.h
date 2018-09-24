#ifndef __SCENEMANAGER_H_INCLUDED__
#define __SCENEMANAGER_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>

#include "maths/Matrix.h"
#include "Device.h"

namespace id
{

	class Driver;
	class SceneNode;
	class CameraSceneNode;
	class TriangleSceneNode;
	class CustomSceneNode;
	class ModelSceneNode;

	class SceneManager
	{
	public:
		SceneManager(SceneManager const&) = delete;
		SceneManager(SceneManager&&) = delete;
		~SceneManager();

		auto operator=(SceneManager const&) -> SceneManager& = delete;
		auto operator=(SceneManager&&) -> SceneManager& = delete;

		Driver* getDriver() {return this->driver;}
		SceneNode* getRootNode() {return this->root_node;}

		Device* getDevice() const {return device;}
		
		static SceneManager* create(Driver*, Device*);

		auto addSceneNode(SceneNode*) -> SceneNode*;
		auto addCameraSceneNode(SceneNode*) -> CameraSceneNode*;
		auto addTriangleSceneNode(SceneNode*) -> TriangleSceneNode*;
		auto addCustomSceneNode(SceneNode*) -> CustomSceneNode*;
		auto addModelSceneNode(SceneNode*) -> ModelSceneNode*;

		void switchShader();

		void update();

	private:
		SceneManager();

		id::log::Log log;

		Driver* driver;
		Device* device;

		GLint world_loc;
		maths::Matrix4 world;

		SceneNode* root_node;
		CameraSceneNode* cam;
	};

}

#endif
