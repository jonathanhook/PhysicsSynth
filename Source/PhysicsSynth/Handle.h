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
#include <MultiTouchEvents/FastDelegate.h>
#include <MultiTouchEvents/MultiTouchEventHandler.h>

namespace JDHUtility 
{ 
	class GLMatrixf;
    class GLTexture;
	class Colour4f;
}

using namespace fastdelegate;
using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class Finger;

	class Handle :
		public MultiTouchEventHandler
	{
	public:
		typedef FastDelegate2<Handle *, const Vector2f &>	DraggedCallback; 
		typedef	FastDelegate1<Handle *>						PressedCallback;

		Handle	(const Point2f &position, float size);
		~Handle	(void);

		bool contains			(const FingerEventArgs &e) const;
		void fingerAdded		(const FingerEventArgs &e);
		void fingerUpdated		(const FingerEventArgs &e);
		void fingerRemoved		(const FingerEventArgs &e);
		void render				(void);
		void setDraggedCallback	(DraggedCallback dragged);
		void setPosition		(const Point2f &position);
		void setPressedCallback	(PressedCallback pressed);

	private:
		static const float			BACKGROUND_ALPHA;
		static const float			BACKGROUND_MASK_ALPHA;
		static const float			CIRCLE_VERTICES;
		static const float			NON_SELECTED_ALPHA_MODIFIER;
		static const float			SELECTED_ALPHA_MODIFIER;
		static const std::string	TEXTURE_PATH;
		static const Colour4f		VALUE_COLOUR;

		DraggedCallback	dragged;
		Finger			*finger;
		bool			fingerDown;
		GLMatrixf		*modelview;
		Point2f			position;
		PressedCallback pressed;
		float			size;
        GLTexture       *texture;

		void saveTransform(void);
	};
}

