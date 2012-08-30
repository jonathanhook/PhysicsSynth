/**
 * Class:	Handle
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <MultiTouchEvents/FastDelegate.h>
#include <MultiTouchEvents/MultiTouchEventHandler.h>

namespace JDHUtility 
{ 
	class GLMatrixf; 
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

		void saveTransform(void);
	};
}

