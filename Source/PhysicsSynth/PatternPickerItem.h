/**
 * Class:	PatternPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "UIElement.h"

namespace PhysicsSynth
{
	class PatternPickerItem :
		public UIElement
	{
	public:
		PatternPickerItem(unsigned int mask, const Point2i &position, unsigned int width);
		~PatternPickerItem(void);

		bool			getChecked	(void) const;
		unsigned int	getMask		(void) const;
		void			render		(void);
		void			setChecked	(bool checked);

	private:
		bool			checked;
		unsigned int	mask;

	};
}

