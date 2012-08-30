/**
 * Class:	EventSource
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <stdio.h>
#include "EventSource.h"
#include <JDHUtility/WindowingUtils.h>

using namespace JDHUtility;

namespace MultiTouchEvents
{
	/* CONSTRUCTORS */
	EventSource::EventSource(void)
	{
		this->eventCallback = NULL;
	}

	EventSource::~EventSource(void)
	{

	}

	/* PUBLIC MEMBER FUNCTIONS */
	void EventSource::setEventCallback(const EventCallback &eventCallback)
	{
		this->eventCallback = eventCallback;
	}

	/* PROTECTED MEMBER FUNCTIONS */
	void EventSource::processPointForWindowTarget(Point2f &p) const
	{
		const Point2f &dims = WindowingUtils::getWindowDimensions();
		const Point2f &pos	= WindowingUtils::getWindowPosition();

		float x = p.getX() - pos.getX();
		float y = p.getY() - pos.getY();
		x /= dims.getX();
		y /= dims.getY();

		//if(squarePixel) // HACK: NOT SURE IF THIS SHOULD BE COMMENTED OR NOT AS DEV-ING WITHOUT A WINDOWS TOUCH DEVICE
		//{
		float ratio = (float)dims.getX() / (float)dims.getY();
		y /= ratio;
		//}

		p.setX(x);
		p.setY(y);
	}
}