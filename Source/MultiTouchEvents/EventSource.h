/**
 * Class:	EventSource
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#ifndef EventSource_H
#define EventSource_H

#include "FastDelegate.h"
#include "FingerEventArgs.h"

using namespace fastdelegate;

namespace MultiTouchEvents
{
	class EventSource
	{
	public:
		typedef FastDelegate4<unsigned int, float, float, FingerEventArgs::EventType> EventCallback;

		EventSource(void);
		~EventSource(void);

		void setEventCallback(const EventCallback &eventCallback);

	protected:
		EventCallback eventCallback;

		void processPointForWindowTarget(Point2f &p) const;
	};
}

#endif

