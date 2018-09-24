#include <iostream>

#include "Driver.h"
#include "SceneNode.h"
#include "CameraSceneNode.h"
#include "TriangleSceneNode.h"
#include "CustomSceneNode.h"
#include "ModelSceneNode.h"
#include "SceneManager.h"

namespace id
{
	SceneManager::SceneManager()
	{
		this->driver = nullptr;
   		this->device = nullptr;
	        this->root_node = nullptr;
                this->cam = nullptr;
	}

	SceneManager::~SceneManager()
	{
		delete this->root_node;

		this->driver = nullptr;
		this->root_node = nullptr;
		this->cam = nullptr;
	}

	SceneManager* SceneManager::create(Driver* driver, Device* device)
	{
		SceneManager* scenemgr = new SceneManager();

		scenemgr->driver = driver;
		scenemgr->device = device;
		scenemgr->root_node = SceneNode::create(scenemgr, nullptr);

		scenemgr->log.setIdentifier("Scene Manager");
		scenemgr->log.setOutput(id::log::BOTH);
		scenemgr->log.info("Creating SceneManager");

		return scenemgr;
	}

	auto SceneManager::addSceneNode(SceneNode* parent) -> SceneNode*
	{
		SceneNode* node = SceneNode::create(this, parent);

		return node;
	}

	auto SceneManager::addCameraSceneNode(SceneNode* parent) -> CameraSceneNode*
	{
		CameraSceneNode* node = CameraSceneNode::create(this->driver, this, parent);

		this->cam = node;

		return node;
	}

	auto SceneManager::addTriangleSceneNode(SceneNode* parent) -> TriangleSceneNode*
	{
		TriangleSceneNode* node = TriangleSceneNode::create(this, parent);

		return node;
	}

	auto SceneManager::addCustomSceneNode(SceneNode* parent) -> CustomSceneNode*
        {
                CustomSceneNode* node = CustomSceneNode::create(this, parent);

                return node;
        }

	auto SceneManager::addModelSceneNode(SceneNode* parent) -> ModelSceneNode*
	{
		ModelSceneNode* node = ModelSceneNode::create(this, parent);

		return node;
	}

	void SceneManager::switchShader()
	{
		this->cam->switchShader();
	}

	void SceneManager::update()
	{
		this->driver->enableDepthTest();
		this->root_node->draw();
	}
}
