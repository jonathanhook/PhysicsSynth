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
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Ndelete.h>
#include "PatternPicker.h"
#include "PatternPickerItem.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int PatternPicker::MAX_COUNT = 32;

	/* Constructors */
	PatternPicker::PatternPicker(unsigned int count, std::string label, const Point2i &position, unsigned int width) :
		LabelledUIElement(label, position, width)
	{
		assert(count <= MAX_COUNT);
		this->count = count;

		dimensions.setY(getLabelHeight() * 2);
		initPatternItems();
	}

	PatternPicker::~PatternPicker(void)
	{
		for(unsigned int i = 0; i < items.size(); i++)
		{
			PatternPickerItem *item = items[i];
			assert(item);

			NDELETE(item);
		}
		items.clear();
	}

	/* Public Member Functions */
	void PatternPicker::fingerAdded(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerAdded(e);

		for(unsigned int i = 0; i < items.size(); i++)
		{
			PatternPickerItem *p = items[i];
			assert(p);

			float px = getSizef(p->getPosition().getX());
			float py = getSizef(p->getPosition().getY());
			float pw = getSizef(p->getDimensions().getX());
			float ph = getSizef(p->getDimensions().getY());
			Point2f pf = e.getPosition();
			pf.translateX(-getSizef(position.getX()));
			pf.translateY(-getSizef(position.getY()));

			if(	(pf.getX() >= px)		&&
				(pf.getX() <= px + pw)	&&
				(pf.getY() >= py)		&&
				(pf.getY() <= py + ph))
			{
				bool checked = !p->getChecked();
				if(checked)
				{
					pattern |= p->getMask();
				}
				else
				{
					pattern &= ~p->getMask();
				}

				p->setChecked(checked);
			}
		}

		if(patternChanged != NULL)
		{
			patternChanged(pattern);
		}
	}

	unsigned int PatternPicker::getPattern(void) const
	{
		return pattern;
	}

	void PatternPicker::render(void)
	{
		LabelledUIElement::render();

		float px = getSizef(position.getX());
		float py = getSizef(position.getY());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px, py, 0.0f);

		for(unsigned int i = 0; i < items.size(); i++)
		{
			PatternPickerItem *item = items[i];
			assert(item);

			item->render();
		}

		glPopMatrix();
	}

	void PatternPicker::setPattern(unsigned int pattern)
	{
		this->pattern = pattern;

		unsigned int mask = 0x1;
		for(unsigned int i = 0; i < items.size(); i++)
		{
			PatternPickerItem *p = items[i];
			assert(p);

			p->setChecked((pattern & mask) != 0);
			mask <<= 1;
		}
	}

	void PatternPicker::setPatternChangedCallback(PatternChangedCallback patternChanged)
	{
		this->patternChanged = patternChanged;
	}

	/* Private Member Functions */
	void PatternPicker::initPatternItems(void)
	{
		unsigned int y			= getLabelHeight();
		unsigned int width		= dimensions.getX() / count;

		unsigned int mask = 0x1;
		for(unsigned int i = 0; i < count; i++)
		{
			unsigned int x = width * i;
			Point2i pos(x, y);
			
			PatternPickerItem *p = new PatternPickerItem(mask, pos, width);
			p->setChecked(true);
			items.push_back(p);

			mask <<= 1;
		}
	}
}
