/**
 * CrossPlatformTime -- Returns the time in milliseconds on Windows and UNIX based systems
 */
#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#pragma comment(lib, "winmm")
#else
#include <sys/timeb.h>
#endif
#include "CrossPlatformTime.h"

#include <GLUT/glut.h>

namespace JDHUtility
{
    int CrossPlatformTime::getTimeMillis(void)
	{

#ifdef _WIN32
		return (long)timeGetTime();
#else
		struct timeb t;
        ftime(&t);
        
        int secs               = (int)t.time;
        unsigned short millis  = t.millitm;

        return (secs * 1000) + millis;
#endif
	}
}

