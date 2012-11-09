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

