/**
 * Class:	CircularWorld
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <math.h>
#include "CircularWorld.h"
#include "Handle.h"
#include "Manager.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	CircularWorld::CIRCLE_RESOLUTION = 32;

	/* Constructors */
	CircularWorld::CircularWorld(unsigned char track, const Point2f &position, const Vector2f &gravity, float size) :
		World(track, position, gravity, size)
	{
		initLimits();
		initHandles();
		setupLimits();
	}

	CircularWorld::~CircularWorld(void)
	{
	}

	/* Public Member Functions */
	bool CircularWorld::contains(const FingerEventArgs &e) const
	{
		assert(modelview != NULL);
		
		Point2f p =	e.getPosition();
		modelview->unTranslatePoint(p);
		modelview->unScalePoint(p);

		return contains(p);
	}

	World::WorldType CircularWorld::getWorldType(void) const
	{
		return CIRCULAR;
	}

	/* Private Member Functions */
	bool CircularWorld::contains(const Point2f &p) const
	{
		float a				= p.getX();
		float b				= p.getY();
		float c				= sqrt((a * a) + (b * b));
		float renderSize	= getRenderSize();

		return c <= renderSize;
	}

	void CircularWorld::initHandles(void)
	{
		float dim = getRenderSize() + (BORDER / 2.0f);

		float x0 = cos((float)M_PI * 0.25f) * dim;
		float y0 = sin((float)M_PI * 0.25f) * dim;
		Point2f p0(x0, y0);

		float x1 = cos((float)M_PI * -0.75f) * dim;
		float y1 = sin((float)M_PI * -0.75f) * dim;
		Point2f p1(x1,	y1);

		if(handleA == NULL && handleB == NULL)
		{
			handleA = new Handle(p0, HANDLE_SIZE);
			handleA->setDraggedCallback(MakeDelegate(this, &CircularWorld::handle_Dragged));
			handleA->setPressedCallback(MakeDelegate(this, &CircularWorld::handle_Pressed));
			registerEventHandler(handleA);

			handleB = new Handle(p1, HANDLE_SIZE);
			handleB->setDraggedCallback(MakeDelegate(this, &CircularWorld::handle_Dragged));
			handleB->setPressedCallback(MakeDelegate(this, &CircularWorld::handle_Pressed));
			registerEventHandler(handleB);
		}
		else
		{
			handleA->setPosition(p0);
			handleB->setPosition(p1);
		}
	}
	
	void CircularWorld::initLimits(void)
	{
		float renderSize = getRenderSize();

		for(unsigned int i = 0; i < CIRCLE_RESOLUTION; i++)
		{
			float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_RESOLUTION) * (float)i; 
			float x		= cos(theta) * renderSize;
			float y		= sin(theta) * renderSize;

			Point2f *p = new Point2f(x, y);
			limits.push_back(p);
		}
	}

	void CircularWorld::limitTranslate(Point2f &centre, float boundingRadius)
	{
		float d, rs;

		do
		{
			float cx	= centre.getX();
			float cy	= centre.getY();
			d			= sqrt((cx * cx) + (cy * cy)) + Manager::descale(boundingRadius);
			rs			= getRenderSize();

			if(d > rs)
			{
				float over = d / rs;
				cx /= over;
				cy /= over;

				centre.setPosition(cx, cy);
			}
		}
		while(d > rs);
	}
}
