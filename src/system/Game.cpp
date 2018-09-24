#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cstring>

#include <stdlib.h>
#include "Device.h"
#include "SceneManager.h"
#include "CameraSceneNode.h"
#include "CustomSceneNode.h"
#include "ModelSceneNode.h"
#include "ManualMesh.h"
#include "Game.h"

Game::Game()
{
	this->device = nullptr;
}

Game::~Game()
{
	this->device = nullptr;
}

auto Game::init(id::Device* device, int argc, char* argv[]) -> Game*
{
	auto* game = new Game();

	game->device = device;

	auto* scenemgr = game->device->getSceneManager();
        auto* root_node = scenemgr->getRootNode();

	scenemgr->addCameraSceneNode(root_node);

	auto* node = scenemgr->addModelSceneNode(root_node);

	std::string model = "";
        std::string texture = "";

        if(argc > 1 && std::strcmp(argv[1], "") != 0)
                model = argv[1];

        if(argc > 2 && std::strcmp(argv[2], "") != 0)
                texture = argv[2];

	node->setMesh(model, texture);

	game->log.setIdentifier("Game");
	game->log.setOutput(id::log::BOTH);
	game->log.info("Inializing Game");

	return game;
}

void Game::createTriforce(id::CustomSceneNode* node)
{

	std::vector<GLfloat> triforce =
                {
                // Front
                20.f,0.0f, 4.f,        0.75f, 0.6f, 0.0f, 1.0f,
                0.0f, 40.f, 4.f,       0.5f, 0.3f, 0.0f, 1.0f,
                -20.f,0.0f, 4.f,       0.75f, 0.6f, 0.0f, 1.0f,

                40.0f, -40.0f, 4.f,      1.0f, 1.0f, 0.0f, 1.0f,
                20.f, 0.0f, 4.f,       0.75f, 0.6f, 0.0f, 1.0f,
                0.0f, -40.0f, 4.f,      1.0f, 1.0f, 0.0f, 1.0f,

                -20.f, 0.0f, 4.f,      0.75f, 0.6f, 0.0f, 1.0f,
                -40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                0.0f, -40.0f, 4.f,      1.0f, 1.0f, 0.0f, 1.0f,

                // Back
                -20.f,0.0f, -4.f,       0.75f, 0.6f, 0.0f, 1.0f,
                0.0f, 40.0f, -4.f,       0.5f, 0.3f, 0.0f, 1.0f,
                20.f,0.0f, -4.f,        0.75f, 0.6f, 0.0f, 1.0f,

                0.0f, -40.0f, -4.f,      1.0f, 1.0f, 0.0f, 1.0f,
                20.f, 0.0f, -4.f,        0.75f, 0.6f, 0.0f, 1.0f,
                40.0f, -40.0f, -4.f,      1.0f, 1.0f, 0.0f, 1.0f,

                -40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                -20.f, 0.0f, -4.f,      0.75f, 0.6f, 0.0f, 1.0f,
                0.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,

                // Left
                0.0f, 40.0f, 4.f,      0.5f, 0.3f, 0.0f, 1.0f,
                0.0f, 40.0f, -4.f,      0.5f, 0.3f, 0.0f, 1.0f,
                -40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,

                -40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                -40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 40.0f, 4.f,      0.5f, 0.3f, 0.0f, 1.0f,

		// Right
                0.0f, 40.0f, -4.f,      0.5f, 0.3f, 0.0f, 1.0f,
                0.0f, 40.0f, 4.f,      0.5f, 0.3f, 0.0f, 1.0f,
                40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,

                40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 40.0f, -4.f,      0.5f, 0.3f, 0.0f, 1.0f,

                // Interior
                20.f,0.0f, 4.f,        0.7f, 0.5f, 0.0f, 1.0f,
                -20.f,0.0f, 4.f,       0.7f, 0.5f, 0.0f, 1.0f,
                -20.f,0.0f, -4.f,       0.7f, 0.5f, 0.0f, 1.0f,

                -20.f,0.0f, -4.f,       0.7f, 0.5f, 0.0f, 1.0f,
                20.f,0.0f, -4.f,        0.7f, 0.5f, 0.0f, 1.0f,
                20.f,0.0f, 4.f,        0.7f, 0.5f, 0.0f, 1.0f,

                20.f, 0.0f, 4.f,       0.7f, 0.5f, 0.0f, 1.0f,
                20.f, 0.0f, -4.f,       0.7f, 0.5f, 0.0f, 1.0f,
                0.0f, -40.0f, -4.f,      0.75f, 0.6f, 0.0f, 1.0f,

                0.0f, -40.0f, -4.f,      0.75f, 0.6f, 0.0f, 1.0f,
                0.0f, -40.0f, 4.f,      0.75f, 0.6f, 0.0f, 1.0f,
                20.f, 0.0f, 4.f,       0.7f, 0.5f, 0.0f, 1.0f,

                -20.f, 0.0f, -4.f,       0.7f, 0.5f, 0.0f, 1.0f,
                -20.f, 0.0f, 4.f,       0.7f, 0.5f, 0.0f, 1.0f,
                0.0f, -40.0f, 4.f,      0.75f, 0.6f, 0.0f, 1.0f,

                0.0f, -40.0f, 4.f,      0.75f, 0.6f, 0.0f, 1.0f,
                0.0f, -40.0f, -4.f,      0.75f, 0.6f, 0.0f, 1.0f,
                -20.f, 0.0f, -4.f,       0.7f, 0.5f, 0.0f, 1.0f,

                // Bottom
                40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                -40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                -40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,

		-40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                40.0f, -40.0f, -4.f,     1.0f, 1.0f, 0.0f, 1.0f,
                40.0f, -40.0f, 4.f,     1.0f, 1.0f, 0.0f, 1.0f,

                };

	node->setMesh(triforce);
}
