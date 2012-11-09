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
#include "MappingButton.h"
#include "MappingGrid.h"

namespace PhysicsSynth
{
	/* Constructors */
	MappingGrid::MappingGrid(std::vector<MappingGridItem> froms, std::vector<MappingGridItem> tos, std::string label, const Point2i &position, const Point2i &dimensions) :
		LabelledUIElement(label, position, dimensions.getX())
	{
		this->froms = froms;
		this->tos	= tos;

		mappingChanged = NULL;

		init();
	}

	MappingGrid::~MappingGrid(void)
	{
		for(unsigned int i = 0; i < mappingButtons.size(); i++)
		{
			NDELETE(mappingButtons[i]);
		}
		mappingButtons.clear();
	}

	/* Public Member Functions */
	void MappingGrid::render(void)
	{
		LabelledUIElement::render();

		for(unsigned int i = 0; i < mappingButtons.size(); i++)
		{
			MappingButton *mb = mappingButtons[i];
			assert(mb);

			mb->render();
		}
	}

	void MappingGrid::setMapping(unsigned int from, unsigned int to)
	{
		for(unsigned int i = 0; i < mappingButtons.size(); i++)
		{
			MappingButton *mb = mappingButtons[i];
			assert(mb);

			if(mb->getFrom().item == from)
			{
				for(unsigned int j = 0; j < tos.size(); j++)
				{
					if(tos[j].item == to)
					{
						mb->setTo(tos[j]);
					}
				}
			}
		}
	}

	void MappingGrid::setMappingChangedCallback(MappingChangedCallback mappingChanged)
	{
		this->mappingChanged = mappingChanged;
	}
	
	/* Private Member Functions */
	void MappingGrid::init(void)
	{
		unsigned int	width			= dimensions.getX();
		unsigned int	height			= getLabelHeight() * 2;
		Point2i			itemDimensions	= Point2i(width, height);

		for(unsigned int i = 0; i < froms.size(); i++)
		{
			MappingGrid::MappingGridItem from = froms[i];

			Point2i itemPos(0, height * i);
			itemPos.translateY(getLabelHeight());
			itemPos.translate(position.getX(), position.getY());

			MappingButton *mb = new MappingButton(from, tos, itemPos, itemDimensions);
			mb->setMappingChangedCallback(MakeDelegate(this, &MappingGrid::mappingButton_MappingChanged));
			registerEventHandler(mb);

			mappingButtons.push_back(mb);
		}

		dimensions.setY((height * froms.size()) + getLabelHeight());
	}

	void MappingGrid::mappingButton_MappingChanged(MappingGridItem from, MappingGridItem to)
	{
		if(mappingChanged != NULL)
		{
			mappingChanged(from, to);
		}
	}
}
