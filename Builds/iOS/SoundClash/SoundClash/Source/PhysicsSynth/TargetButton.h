/**
 * Class:	TargetButton
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Vector2f.h>
#include "Button.h"

namespace JDHUtility { class GLVbo; }

namespace PhysicsSynth
{
	class TargetButton :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<const Vector2f &> TargetChangedCallback;

		TargetButton(std::string text, const Point2i &position, unsigned int width);
		~TargetButton(void);

		void			fingerAdded				(const FingerEventArgs &e);
		void			fingerUpdated			(const FingerEventArgs &e);
		void			fingerRemoved			(const FingerEventArgs &e);
		const Vector2f	&getTargetPosition		(void) const;
		void			render					(void);
		void			setTargetChangedCallback(TargetChangedCallback targetChanged);
		void			setTargetPosition		(const Vector2f &targetPosition);

	private:
		static const float SNAP_THRESHOLD;

		TargetChangedCallback	targetChanged;
		Vector2f				targetPosition;
        GLVbo                   *hVbo;
        GLVbo                   *vVbo;
        
        
		void updateTargetPosition(const FingerEventArgs &e);
	};
}

