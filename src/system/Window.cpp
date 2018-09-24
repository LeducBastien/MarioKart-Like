#include "Window.h"

namespace id
{

	Window::Window()
	{
	}

	Window::~Window()
	{
		this->window = nullptr;
	}

	Window* Window::create(std::string title, int width, int height)
	{
		auto* win = new Window();

		win->log.setIdentifier("Window");
		win->log.setOutput(id::log::BOTH);
		win->log.info("Creating Window");

		win->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
		if(!win->window)
			win->log.alert("Could not create SDL_Window");

		return win;
	}

	void Window::update()
	{
		SDL_GL_SwapWindow(this->window);
	}

	void Window::close()
	{
		this->log.info("Closing Window");

		SDL_DestroyWindow(this->window);
	}
}
