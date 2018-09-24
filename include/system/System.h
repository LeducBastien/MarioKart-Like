#ifndef __SYSTEM_H_INCLUDED__
#define __SYSTEM_H_INCLUDED__

#include <memory>
#include "Log.h"

namespace id
{
	class Device;
	class PolEvent;
}

class Game;

class System
{
public:
	System(System const&) = delete;
	System(System&&) = delete;
	~System();

	static System* init(int argc, char* argv[]);
	void run();

private:
	System();

	id::log::Log log;

	id::Device* device;
	Game* game;

	bool running = true;
};



#endif
