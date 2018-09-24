#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__

#include <SDL.h>
#include <string>
#include "Log.h"

namespace id
{
	class Window
	{
	public:
		Window(Window const&) = delete;
		Window(Window&&) = delete;
		~Window();

		auto operator=(Window const&) -> Window& = delete;
		auto operator=(Window&&) -> Window& = delete;

		static Window* create(std::string, int, int);

		SDL_Window* getWindow() {return this->window;}

		void update();
		void close();
	private:
		Window();
		id::log::Log log;

		SDL_Window* window;
	};
}

#endif
