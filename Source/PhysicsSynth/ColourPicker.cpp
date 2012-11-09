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
#include <JDHUtility/Ndelete.h>
#include "ColourPicker.h"
#include "ColourPickerItem.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	ColourPicker::COLUMNS		= 8;
	const unsigned int	ColourPicker::PICKER_HEIGHT	= 17;

	/* Constructors */
	ColourPicker::ColourPicker(std::vector<SoundConfig *> items, std::string label, const Point2i &position, unsigned int width) :
		LabelledUIElement(label, position, width)
	{
		dimensions.setY(getLabelHeight() + (winHeight / PICKER_HEIGHT));

		init(items);
	}

	ColourPicker::~ColourPicker(void)
	{
		for(unsigned int i = 0; i < colours.size(); i++)
		{
			NDELETE(colours[i]);
		}
		colours.clear();
	}

	/* Public Member Functions */
	void ColourPicker::render(void)
	{
		LabelledUIElement::render();

		for(unsigned int i = 0; i < colours.size(); i++)
		{
			ColourPickerItem *c = colours[i];
			assert(c);

			c->render();
		}
	}

	void ColourPicker::setSelectedItem(ColourPickerItem *item)
	{
		item->setChecked(true);

		for(unsigned int i = 0; i < colours.size(); i++)
		{
			ColourPickerItem *other = colours[i];
			assert(other);

			if(item != other)
			{
				other->setChecked(false);
			}
		}

		if(selectionChanged != NULL)
		{
			selectionChanged(item->getColour());
		}
	}

	void ColourPicker::setSelectedItem(SoundConfig *item)
	{
		ColourPickerItem *cp = NULL;
		for(unsigned int i = 0; i < colours.size(); i++)
		{
			ColourPickerItem *other = colours[i];
			assert(other);

			if(other->getColour() == item)
			{
				cp = other;
			}
		}

		if(cp != NULL)
		{
			setSelectedItem(cp);
		}
	}

	void ColourPicker::setPosition(const Point2i &position)
	{
		unsigned int tx = position.getX() - this->position.getX();
		unsigned int ty = position.getY() - this->position.getY();

		this->position = position;

		// update children
		for(unsigned int i = 0; i < colours.size(); i++)
		{
			ColourPickerItem *item = colours[i];
			assert(item);

			Point2i itemPos = item->getPosition();
			itemPos.translateX(tx);
			itemPos.translateY(ty);

			item->setPosition(itemPos);
		}
	}

	void ColourPicker::setSelectionChangedCallback(SelectionChangedCallback selectionChanged)
	{
		this->selectionChanged = selectionChanged;
	}

	/* Private Memeber Functions */
	void ColourPicker::colourPickerItem_Checked(ColourPickerItem *item)
	{
		setSelectedItem(item);
	}

	void ColourPicker::init(std::vector<SoundConfig *> items)
	{
		unsigned int width	= 0;
		unsigned int height = 0;

		if(items.size() >= COLUMNS)
		{
			width	= dimensions.getX() / COLUMNS;
			height	= (dimensions.getY() - getLabelHeight()) / (items.size() / COLUMNS);;
		}
		else
		{
			width	= dimensions.getX() / items.size();
			height	= dimensions.getY() - getLabelHeight(); 
		}

		Point2i	itemDimensions = Point2i(width, height);

		unsigned int size = items.size();
		for(unsigned int i = 0; i < size; i++)
		{
			SoundConfig *item = items[i];
			assert(item);
		
			unsigned int column	= i % COLUMNS;
			unsigned int row	= i / COLUMNS;

			Point2i itemPos(width * column, height * row);
			itemPos.translate(position.getX(), position.getY() + getLabelHeight());

			ColourPickerItem *cpi = new ColourPickerItem(item, itemPos, itemDimensions);
			cpi->setCheckedCallback(MakeDelegate(this, &ColourPicker::colourPickerItem_Checked));

			colours.push_back(cpi);
			registerEventHandler(cpi);
		}
	}
}