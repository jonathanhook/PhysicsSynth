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
#include <JDHUtility/Colour4f.h>
#include <MultiTouchEvents/MultiTouchEventHandler.h>
#include <JDHUtility/Point2i.h>
#include "FastDelegate.h"

namespace JDHUtility { class GLTextureFont; }

using namespace fastdelegate;
using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class UIElement :
		public MultiTouchEventHandler
	{
	public:
		typedef FastDelegate1<UIElement *> ClickedCallback;
		typedef FastDelegate1<UIElement *> PressedCallback;
		typedef FastDelegate1<UIElement *> ReleasedCallback;

		static float getSizef(unsigned int pixels); 

		UIElement	(const Point2i &position, const Point2i &dimensions);
		~UIElement	(void);

		virtual bool	contains			(const FingerEventArgs &e) const;
		virtual void	fingerAdded			(const FingerEventArgs &e);
		virtual void	fingerUpdated		(const FingerEventArgs &e);
		virtual void	fingerRemoved		(const FingerEventArgs &e);
		const Point2i	&getDimensions		(void) const;
		const Point2i	&getPosition		(void) const;
		virtual void	render				(void) = 0;
		void			setClickedCallback	(ClickedCallback clicked);
		void			setDimensions		(const Point2i &dimensions);
		virtual void	setPosition			(const Point2i &position);
		void			setPressedCallback	(PressedCallback pressed);
		void			setReleasedCallback	(ReleasedCallback released);

	protected:
		static const unsigned int	BORDER;
		static const Colour4f		DARK_COLOUR;
		static const unsigned int	LABEL_HEIGHT_DIV;
		static const Colour4f		LIGHT_COLOUR;
        static const Colour4f       MID_COLOUR;
		static const Colour4f		VALUE_COLOUR;
        static const Colour4f       FONT_COLOUR;

		bool				captured;
		unsigned int		capturedId;
		ClickedCallback		clicked;
		Point2i				dimensions;
		PressedCallback		pressed;
		Point2i				position;
		ReleasedCallback	released;
		bool				selected;
		int					winWidth;
		int					winHeight;

		unsigned int getLabelHeight	(void) const;
	};
}

