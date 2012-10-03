/**
 * Class:	SquareWorld
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include "Handle.h"
#include "Manager.h"
#include "SquareWorld.h"

namespace PhysicsSynth
{
	/* Constructors */
	SquareWorld::SquareWorld(unsigned char track, const Point2f &position, const Vector2f &gravity, float size) :
		World(track, position, gravity, size)
	{
		initLimits();
		initHandles();
		setupLimits();
	}

	SquareWorld::~SquareWorld(void)
	{
	}

	/* Public Member Functions */
	bool SquareWorld::contains(const FingerEventArgs &e) const
	{
		assert(modelview != NULL);
		
		Point2f p =	e.getPosition();
		modelview->unTranslatePoint(p);
		modelview->unScalePoint(p);

		return contains(p);
	}

	World::WorldType SquareWorld::getWorldType(void) const
	{
		return SQUARE;
	}

	/* Private Member Functions */
	bool SquareWorld::contains(const Point2f &p) const
	{
		float x		= p.getX();
		float y		= p.getY();
		float dim	= getRenderSize();

		return	(x >= -dim)	&&
				(x <= dim)	&&
				(y >= -dim) &&
				(y <= dim);
	}

	void SquareWorld::initHandles(void)
	{
		float dim = getRenderSize() + (BORDER / 2.0f);

		Point2f p0(-dim, -dim);
		Point2f p1(dim,	dim);

		if(handleA == NULL && handleB == NULL)
		{
			handleA = new Handle(p0, HANDLE_SIZE);
			handleA->setDraggedCallback(MakeDelegate(this, &SquareWorld::handle_Dragged));
			registerEventHandler(handleA);

			handleB = new Handle(p1, HANDLE_SIZE);
			handleB->setDraggedCallback(MakeDelegate(this, &SquareWorld::handle_Dragged));
			registerEventHandler(handleB);
		}
		else
		{
			handleA->setPosition(p0);
			handleB->setPosition(p1);
		}
	}

	void SquareWorld::initLimits(void)
	{
		float dim = getRenderSize();

		Point2f *p0 = new Point2f(-dim, -dim);
		Point2f *p1 = new Point2f(dim,	-dim);
		Point2f *p2 = new Point2f(dim,	dim);
		Point2f *p3 = new Point2f(-dim, dim);

		limits.push_back(p0);
		limits.push_back(p1);
		limits.push_back(p2);
		limits.push_back(p3);
	}

	void SquareWorld::limitTranslate(Point2f &centre, float boundingRadius)
	{
		float cx	= centre.getX();
		float cy	= centre.getY();
		float rs	= getRenderSize();
		float br	= Manager::descale(boundingRadius);

		if((cx + br) > rs)
		{
			cx = rs - br;
		}
		else if((cx - br) < -rs)
		{
			cx = -rs + br;
		}

		if((cy + br) > rs)
		{
			cy = rs - br;
		}
		else if((cy - br) < -rs)
		{
			cy = -rs + br;
		}

		centre.setPosition(cx, cy);
	}
}
