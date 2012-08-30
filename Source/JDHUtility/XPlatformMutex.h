/**
 * Class:	XPlatformMutex
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace JDHUtility
{
	class XPlatformMutex
	{
	public:
		XPlatformMutex(void);
		~XPlatformMutex(void);

		void wait	(void) const;
		void release(void) const;

#ifdef _WIN32
		void *hMutex;
#else
        pthread_mutex_t *mutex;
#endif
	};
}

