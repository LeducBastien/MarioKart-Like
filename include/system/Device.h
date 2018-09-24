#ifndef __DEVICE_H_INCLUDED__
#define __DEVICE_H_INCLUDED__

#include <memory>
#include "Log.h"

namespace id
{
	class Window;
	class Driver;
	class SceneManager;
	class GUI;
	class PollEvent;

    class Device
    {
    public:
        ~Device();

        Device(Device const&) = delete;
        Device(Device&&) = delete;
        auto operator=(Device const&) -> Device& = delete;
        auto operator=(Device&&) -> Device& = delete;

	Driver* getDriver() {return this->driver;}
	SceneManager* getSceneManager() {return this->scenemgr;}

	PollEvent* getEvent() const {return this->evt;}

	void stop() {this->running = false;}

        static auto create() -> Device*;

	void setDefaultParameters();
        void close();
        void run();

    private:
        Device();

	id::log::Log log;

	Window* window;
	Driver* driver;
	SceneManager* scenemgr;
	GUI* gui;

	PollEvent* evt;

	bool running = true;
    };
}

#endif
