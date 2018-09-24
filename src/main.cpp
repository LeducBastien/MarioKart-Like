#include "System.h"

int main ( int argc , char* argv[])
{
	System* sys = System::init(argc, argv);
	sys->run();
	delete sys;

	return EXIT_SUCCESS;
}
