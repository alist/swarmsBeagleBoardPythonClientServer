#define API_TYPE

#ifndef DRIVELIB
#define DRIVELIB
#endif

#ifdef BUILD_DLL
#define API_TYPE __declspec(dllexport)
#else
#define API_TYPE __declspec(dllimport)
#endif

extern "C" API_TYPE void printGreeting();
