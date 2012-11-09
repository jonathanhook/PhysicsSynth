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
