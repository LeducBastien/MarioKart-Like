#ifndef __GUI_H_INCLUDED__
#define __GUI_G_INCLUDED__

#include <imgui.h>
#include <SDL.h>
#include "Log.h"

namespace id
{
	class GUI
	{
	public:
		GUI(GUI const&) = delete;
		GUI(GUI&&) = delete;
		~GUI();

		auto operator=(GUI const&) -> GUI& = delete;
		auto operator=(GUI&&) -> GUI& = delete;

		static auto create(SDL_Window*) -> GUI*;

		void setKeyMap();

		void newFrame();
		void mouseEvent(ImGuiIO&);

		void render();

		void close();

	private:
		GUI();

		id::log::Log log;

		SDL_Window* window;
		double g_Time = 0.0;
	};
}

#endif
