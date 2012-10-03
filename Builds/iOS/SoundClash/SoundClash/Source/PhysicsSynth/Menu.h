/**
 * Class:	Menu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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
		typedef enum Borders
		{
			TOP		= 0x1,
			BOTTOM	= 0x2,
			LEFT	= 0x4,
			RIGHT	= 0x8
		};

		typedef enum MenuMode { CREATE, INSPECT };

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

