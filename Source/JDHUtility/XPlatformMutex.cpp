/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
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
		pthread_mutex_init(&mutex, NULL);
	}
    
	XPlatformMutex::~XPlatformMutex(void)
	{
        pthread_mutex_destroy(&mutex);
	}
    
	void XPlatformMutex::wait(void)
	{
        pthread_mutex_lock(&mutex);
	}
    
	void XPlatformMutex::release(void)
	{
		pthread_mutex_unlock(&mutex);
	}
#endif
}
