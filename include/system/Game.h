#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <memory>
#include "Log.h"

namespace id
{
	class Device;
	class CustomSceneNode;

}

class Game
{
public:
	Game(Game const&) = delete;
	Game(Game&&) = delete;
	~Game();

	auto operator=(Game const&) -> Game& = delete;
	auto operator=(Game&&) -> Game& = delete;

	static auto init(id::Device*, int, char*[]) -> Game*;

	void createTriforce(id::CustomSceneNode*);

private:
	Game();
	id::log::Log log;

	id::Device* device;
};

#endif
