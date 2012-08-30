/**
 * Class:	LabelledUIElement
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Colour4f.h>
#include <string>
#include "UIElement.h"

namespace PhysicsSynth
{
	class LabelledUIElement : 
		public UIElement
	{
	public:
		LabelledUIElement	(std::string label, const Point2i &position, unsigned int width);
		~LabelledUIElement	(void);

		virtual void render(void);

	private:
		unsigned int	dl;
		std::string		label;

	};
}

