/**
 * Class:	PushButton
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "UIElement.h"

namespace JDHUtility { class GLTexture; }

namespace PhysicsSynth
{
	class PushButton :
		public UIElement
	{
	public:
		PushButton(std::string texturePath, const Point2i &position, const Point2i &dimensions);
		~PushButton(void);

		void render(void);

	private:
		GLTexture *texture;

	};
}

