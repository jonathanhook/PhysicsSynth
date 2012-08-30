/**
 * Class:	Button
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/GLTexture.h>
#include "LabelledUIElement.h"

using namespace JDHUtility;

namespace PhysicsSynth
{
	class Button :
		public UIElement
	{
	public:
		Button(std::string label, const Point2i &position, unsigned int width);
		~Button(void);

		virtual void render(void);

	private:
		unsigned int	buttonDl;
		std::string		label;
	};
}

