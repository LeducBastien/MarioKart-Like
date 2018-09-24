#include <cstring>
#include "Device.h"
#include "Game.h"
#include "System.h"

System* System::init(int argc, char* argv[])
{
	System* sys = new System();

	sys->log.setIdentifier("System");
	sys->log.setOutput(id::log::BOTH);
	sys->log.info("Initializing System");

	sys->device = id::Device::create();
	sys->game = Game::init(sys->device, argc, argv);

	return sys;
}

void System::run()
{
	this->device->run();
	this->device->close();
}

System::System()
{
}

System::~System()
{
	delete this->device;
	delete this->game;

	this->device = nullptr;
	this->game = nullptr;
}
