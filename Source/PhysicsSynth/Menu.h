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
#pragma once
#include "UIElement.h"

namespace JDHUtility { class GLVbo; }

namespace PhysicsSynth
{
	class Menu : 
		public UIElement
	{
	public:
		enum Borders
		{
			TOP		= 0x1,
			BOTTOM	= 0x2,
			LEFT	= 0x4,
			RIGHT	= 0x8
		};

		enum MenuMode { CREATE, INSPECT };

		Menu(const Point2i &position, unsigned int width, unsigned char borderState = (TOP | BOTTOM | LEFT | RIGHT), MenuMode mode = CREATE);
		~Menu(void);

		virtual	void	initMenuItems	(void) = 0;
		void			fingerAdded		(const FingerEventArgs &e);
		void			fingerUpdated	(const FingerEventArgs &e);
		void			fingerRemoved	(const FingerEventArgs &e);
		virtual void	render			(void);
		void			setBorderState	(unsigned char borderState);
		void			setPosition		(const Point2i &position);
		virtual void	setValues		(void) = 0;

	protected:
		static const std::string	CREATE_TEXTURE;
		static const std::string	ERASE_TEXTURE;

		unsigned char				borderState;
		std::vector<UIElement *>	menuItems;
		MenuMode					mode;

		void addMenuItem(UIElement &item);

	private:
		static const Colour4f BACKGROUND_MASK_COLOUR;
		static const Colour4f BORDER_COLOUR;

		Point2i			addCursor;
		unsigned int	maxY;
        GLVbo           *topVbo;
        GLVbo           *bottomVbo;
        GLVbo           *leftVbo;
        GLVbo           *rightVbo;
	};
}

