#ifndef __EVENTMANAGER_H_INCLUDED__
#define __EVENTMANAGER_H_INCLUDED__

namespace id
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		bool isRunning() {return this->running;}

		void update();
	private:
		bool running;
	};
}

#endif
