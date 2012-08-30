/**
 * Class:	MultiTouchEventManager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#ifndef MultiTouchEventManager_H
#define MultiTouchEventManager_H

#include <map>
#include <queue>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/Point2f.h>
#include "FingerEventArgs.h"

using namespace JDHUtility;

namespace JDHUtility 
{ 
	class XPlatformMutex;
}

namespace MultiTouchEvents
{
	class EventSource;
	class MultiTouchEventHandler;

	class MultiTouchEventManager
	{
	public:
		MultiTouchEventManager	(bool dispatchEvents = true);
		~MultiTouchEventManager	(void);

		void dispatchAllEvents		(void);
		bool isPeekEnabled			(void);
		void raiseEvent				(unsigned int id, float x, float y, FingerEventArgs::EventType type);
		void raiseKeyEvent			(unsigned char key, bool pressed);
		void registerEventHandler	(MultiTouchEventHandler *eventHandler);
		void registerEventSource	(EventSource *source);
		void release				(unsigned int id);
		void setPeekEnabled			(bool peekEnabled);
		void unregisterEventHandler	(MultiTouchEventHandler *eventHandler);

	private:
		std::map<int, MultiTouchEventHandler *>	captured;
		bool									dispatchEvents;
		std::queue<FingerEventArgs *>			eventQueue;
		std::vector<MultiTouchEventHandler *>	handlers;
		bool peekEnabled;
		
		void			dispatchAddedEvent		(FingerEventArgs *e);
		void			dispatchEvent			(FingerEventArgs *e);
		void			dispatchRemovedEvent	(FingerEventArgs *e);
		void			dispatchUpdatedEvent	(FingerEventArgs *e);
		virtual void	peek					(const FingerEventArgs &e);

		XPlatformMutex *mutex;
	};
}
#endif
