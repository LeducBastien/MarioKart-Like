#ifndef __EVENT_H_INCLUDED__
#define __EVENT_H_INCLUDED__

#include <SDL.h>
#include <string>
#include "ModelSceneNode.h"


namespace id
{

class Device;

class PollEvent
{
public:
	PollEvent(PollEvent const&) = delete;
	PollEvent(PollEvent&&) = delete;
	~PollEvent();
	
	auto operator=(PollEvent const&) -> PollEvent& = delete;
	auto operator=(PollEvent&&) -> PollEvent& = delete;

	static auto getKeyInput() -> SDL_Scancode;
	static bool mouseIsClicked();
	static int getMouseRelX();
	static int getMouseRelY();
	static int getMouseX();
        static int getMouseY();

	int getScale() const {return scale;} 

	static bool isHold();
	static void setHold(bool);

	static auto init(Device*) -> PollEvent*;

	void update();
	void reset();
	void eventListener(SDL_Event const&);
	void keyDownEvent(SDL_Event const&);

	void setModelNode(ModelSceneNode* node) {model_node = node;}

private:
	PollEvent();

	Device* device;

	ModelSceneNode* model_node;

	static SDL_Scancode key;

	static bool hold;

	static bool mouse_click;

	static int mouse_rel_x;
	static int mouse_rel_y;
	static int mouse_x;
        static int mouse_y;
	static int scale;
};

}

#endif
