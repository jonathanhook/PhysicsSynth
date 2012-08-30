/**
 * Class:	PatternPicker
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class PatternPickerItem;

	class PatternPicker :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<unsigned int> PatternChangedCallback;

		PatternPicker	(unsigned int count, std::string label, const Point2i &position, unsigned int width);
		~PatternPicker	(void);

		void			fingerAdded					(const FingerEventArgs &e);
		unsigned int	getPattern					(void) const;
		void			render						(void);
		void			setPattern					(unsigned int pattern);
		void			setPatternChangedCallback	(PatternChangedCallback patternChanged);

	private:
		static const unsigned int MAX_COUNT;

		unsigned int						count;
		unsigned int						pattern;
		PatternChangedCallback				patternChanged;
		std::vector<PatternPickerItem *>	items;

		void initPatternItems(void);
	};
}

