/**
 * Class:	XPlatformMutex
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include "XPlatformMutex.h"

namespace JDHUtility
{
#ifdef _WIN32
	XPlatformMutex::XPlatformMutex(void)
	{
		hMutex = CreateMutex(NULL, FALSE, NULL);
	}

	XPlatformMutex::~XPlatformMutex(void)
	{
		if (hMutex != NULL) 
		{ 
			CloseHandle((HANDLE)hMutex); 
		}
	}

	void XPlatformMutex::wait(void) const
	{
		WaitForSingleObject((HANDLE)hMutex, INFINITE);
	}

	void XPlatformMutex::release(void) const
	{
		ReleaseMutex((HANDLE)hMutex);
	}
#else
   	XPlatformMutex::XPlatformMutex(void)
	{
		//pthread_mutex_init(mutex, NULL);
	}
    
	XPlatformMutex::~XPlatformMutex(void)
	{
		if (mutex != NULL)
		{
			 //pthread_mutex_destroy(mutex);
		}
	}
    
	void XPlatformMutex::wait(void) const
	{
		//pthread_mutex_lock(mutex);
	}
    
	void XPlatformMutex::release(void) const
	{
		//pthread_mutex_unlock(mutex);
	}
#endif
}
