#define BUILD_DLL

#ifndef DRIVELIB
#define DRIVELIB


#if defined (__GNUC__) 
  #define API_TYPE __attribute__ ((__visibility__("default")))
#elif defined (WIN32)

#ifdef BUILD_DLL
#define API_TYPE __declspec(dllexport)
#else
#define API_TYPE __declspec(dllimport)
#endif

#else
#warning "no supported build"
#endif

extern "C" API_TYPE void printGreeting(void);
#endif
