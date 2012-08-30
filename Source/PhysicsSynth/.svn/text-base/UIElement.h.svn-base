/**
 * Class:	UIElement
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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
		static const Colour4f		VALUE_COLOUR;

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

