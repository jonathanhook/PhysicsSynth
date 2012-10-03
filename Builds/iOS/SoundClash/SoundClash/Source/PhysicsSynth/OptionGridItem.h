/**
 * Class:	OptionGridItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "OptionGrid.h"
#include "UIElement.h"

namespace JDHUtility { class GLFontRenderer; }

using namespace JDHUtility;

namespace PhysicsSynth
{
	class OptionGridItem : 
		public UIElement
	{
	public:
		typedef FastDelegate1<OptionGridItem *> CheckedCallback;

		OptionGridItem(const OptionGrid::Option &option, const Point2i &position, const Point2i &dimensions);
		~OptionGridItem(void);
			
		void						fingerAdded			(const FingerEventArgs &e);
		const OptionGrid::Option	&getOption			(void) const;
		bool						isChecked			(void) const;
		void						render				(void);
		void						setChecked			(bool checked);
		void						setCheckedCallback	(CheckedCallback checkedCallback);

	private:
		CheckedCallback		checkedCallback;
		bool				checked;
		OptionGrid::Option	option;
	};
}

