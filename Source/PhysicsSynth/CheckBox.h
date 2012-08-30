/**
 * Class:	CheckBox
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <string>
#include "Button.h"

namespace PhysicsSynth
{
	class CheckBox :
		public Button
	{
	public:
		typedef FastDelegate1<bool> CheckedChangedCallback;

		CheckBox	(std::string label, const Point2i &position, unsigned int width);
		~CheckBox	(void);

		void fingerAdded				(const FingerEventArgs &e);
		void render						(void);
		void setCheckedChangedCallback	(CheckedChangedCallback checkedChanged);
		void setIsChecked				(bool isChecked);

	private:
		CheckedChangedCallback	checkedChanged;
		unsigned int			checkedDl;
		bool					isChecked;
	};
}
