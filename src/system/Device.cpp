#include "Device.h"
#include "PollEvent.h"
#include "GUI.h"
#include "Driver.h"
#include "Window.h"
#include "SceneManager.h"
#include "maths/Matrix.h"
#include "maths/tools.h"

#include <imgui.h>
#include <new>
#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>

namespace id {

auto	Device::create() -> Device*
{
	auto*	dev = new (std::nothrow) Device;

	SDL_assert(dev);

	dev->log.setIdentifier("Device");
	dev->log.setOutput(id::log::BOTH);
	dev->log.info("Initializing Device");

	dev->setDefaultParameters();

	return dev;
}

void Device::setDefaultParameters()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->window = Window::create("OpenGL 4.2", 800, 800);
	this->evt = PollEvent::init(this);
	this->driver = Driver::create(this->window->getWindow());
	this->gui = GUI::create(this->window->getWindow());
	this->scenemgr = SceneManager::create(this->driver, this);
}

void Device::run()
{
	while (this->running)
        {
		this->gui->newFrame();
		this->evt->update();
		this->driver->update(this->scenemgr);
		this->gui->render();
                this->window->update();
        }

}

void Device::close()
{
	this->log.info("Closing Device");

	glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        this->driver->close();
	this->window->close();

	ImGui::Shutdown();
}

Device::~Device()
{
	SDL_Quit();

	delete this->driver;
	delete this->window;
	delete this->scenemgr;
	delete this->evt;

	this->driver = nullptr;
	this->window = nullptr;
	this->scenemgr = nullptr;
	this->evt = nullptr;
	
}

Device::Device()
{
	if(!SDL_Init(SDL_INIT_EVERYTHING))
		this->log.error("Could not initialize SDL");

	this->driver = nullptr;
        this->window = nullptr;
        this->scenemgr = nullptr;
        this->evt = nullptr;

}

}
