/**
 * Class:	Slider
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <string>
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class Slider :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<float> ValueChangedCallback;

		Slider(std::string label, const Point2i &position, unsigned int width);
		~Slider(void);

		void	fingerAdded				(const FingerEventArgs &e);
		void	fingerUpdated			(const FingerEventArgs &e);
		void	fingerRemoved			(const FingerEventArgs &e);
		float	getValue				(void) const;
		void	render					(void);
		void	setValue				(float value);
		void	setValueChangedCallback	(ValueChangedCallback valueChanged);

	private:
		float					value;
		ValueChangedCallback	valueChanged;

		void updateValue(const FingerEventArgs &e);
	};
}

