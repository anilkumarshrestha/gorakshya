// Know OS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WIN64)
	#define OPERATING_SYSTEM_WINDOWS
#elif defined(__linux__)
	#define OPERATING_SYSTEM_LINUX
#else
	#define OPERATING_SYSTEM_OTHER
#endif

#include "PfWindow.hpp"