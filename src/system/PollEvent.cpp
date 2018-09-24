#include <iostream>
#include <imgui.h>

#include "ModelMesh.h"
#include "Device.h"
#include "PollEvent.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "ModelSceneNode.h"

namespace id
{
	SDL_Scancode PollEvent::key = SDL_SCANCODE_UNKNOWN;
	bool PollEvent::hold = false;
	bool PollEvent::mouse_click = true;
	int PollEvent::mouse_rel_x = 0;
	int PollEvent::mouse_rel_y = 0;

	int PollEvent::scale = 1;
	int PollEvent::mouse_x = 0;
	int PollEvent::mouse_y = 0;

	PollEvent::PollEvent()
	{
		this->device = nullptr;
	}

	PollEvent::~PollEvent()
	{
		//delete this->device;
		this->device = nullptr;
	}

	auto PollEvent::init(Device* device) -> PollEvent*
	{
		auto* evt = new PollEvent();

		evt->device = device;

		return evt;
	}

	auto PollEvent::getKeyInput() -> SDL_Scancode
	{
		return PollEvent::key;
	}

	bool PollEvent::mouseIsClicked()
	{
		return PollEvent::mouse_click;
	}

	int PollEvent::getMouseRelX()
	{
		return PollEvent::mouse_rel_x;
	}

	int PollEvent::getMouseRelY()
	{
		return PollEvent::mouse_rel_y;
	}

	int PollEvent::getMouseX()
	{
		return PollEvent::mouse_x;
	}

	int PollEvent::getMouseY()
	{
		return PollEvent::mouse_y;
	}

	bool PollEvent::isHold()
	{
		return PollEvent::hold;
	}

	void PollEvent::setHold(bool hold)
	{
		PollEvent::hold = hold;
	}

	void PollEvent::update()
	{
		SDL_assert(this->device);

		this->reset();

		SDL_Event evt;

		while(SDL_PollEvent(&evt))
		{
			this->eventListener(evt);
		}
	}

	void PollEvent::reset()
	{
		PollEvent::mouse_rel_x = 0;
                PollEvent::mouse_rel_y = 0;
	}

	void PollEvent::eventListener(SDL_Event const& evt)
	{
		switch(evt.type)
		{
			case SDL_QUIT:
				this->device->stop();
			break;

			case SDL_KEYDOWN:
				PollEvent::key = evt.key.keysym.scancode;
			break;
			
			case SDL_KEYUP:
			{
				PollEvent::key = SDL_SCANCODE_UNKNOWN;
				PollEvent::hold = false;
			}
			break;

			case SDL_TEXTINPUT:
			{
				ImGuiIO& io = ImGui::GetIO();
				io.AddInputCharactersUTF8(evt.text.text);
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				if (evt.button.button == SDL_BUTTON_LEFT)
					PollEvent::mouse_click = true;
			}
			break;

			case SDL_MOUSEBUTTONUP:
			{
				if (evt.button.button == SDL_BUTTON_LEFT)
					PollEvent::mouse_click = false;
			}
			break;

			case SDL_MOUSEMOTION:
			{
				PollEvent::mouse_rel_x = evt.motion.xrel;
				PollEvent::mouse_rel_y = evt.motion.yrel;

				PollEvent::mouse_x = evt.motion.x;
				PollEvent::mouse_y = evt.motion.y;
			}
			break;

			default: break;
		}
	}
}
