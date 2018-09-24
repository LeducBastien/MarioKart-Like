#include <iostream>
#include <SDL.h>
#include <imgui.h>

#include "PollEvent.h"
#include "ImGuiImpl.h"
#include "GUI.h"

namespace id
{
	GUI::GUI()
	{
		this->window = nullptr;
	}

	GUI::~GUI()
	{
		this->window = nullptr;
	}

	auto GUI::create(SDL_Window* window) -> GUI*
	{
		auto* gui = new GUI();

		gui->window = window;

		gui->log.setIdentifier("GUI");
		gui->log.setOutput(id::log::BOTH);
		gui->log.info("Creating GUI");

		ImGuiImpl::init();

		gui->setKeyMap();

		return gui;
	}

	void GUI::setKeyMap()
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;                     // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
		io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SDLK_a;
		io.KeyMap[ImGuiKey_C] = SDLK_c;
		io.KeyMap[ImGuiKey_V] = SDLK_v;
		io.KeyMap[ImGuiKey_X] = SDLK_x;
		io.KeyMap[ImGuiKey_Y] = SDLK_y;
		io.KeyMap[ImGuiKey_Z] = SDLK_z;

	}

	void GUI::newFrame()
	{
		ImGuiIO& io = ImGui::GetIO();

		int w, h;
		SDL_GetWindowSize(this->window, &w, &h);
		io.DisplaySize = ImVec2((float)w, (float)h);

		Uint32  time = SDL_GetTicks();
		double current_time = time / 1000.0;
		io.DeltaTime = this->g_Time > 0.0 ? (float)(current_time - this->g_Time) : (float)(1.0f/60.0f);
		this->g_Time = current_time;

		this->mouseEvent(io);

		ImGui::NewFrame();
	}

	void GUI::mouseEvent(ImGuiIO& io)
	{
		bool is_clicked = PollEvent::mouseIsClicked();
		int mouse_x = PollEvent::getMouseX();
		int mouse_y = PollEvent::getMouseY();

		io.MouseDown[0] = is_clicked;

		if (SDL_GetWindowFlags(this->window) & SDL_WINDOW_MOUSE_FOCUS)
			io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
		else
			io.MousePos = ImVec2(-1,-1);
		
	}

	void GUI::render()
	{
		ImGui::Render();
	} 

	void GUI::close()
	{
		this->log.info("Removing GUI");

		ImGui::Shutdown();
	}
}
