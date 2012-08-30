/**
 * Class:	RSTObject
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/GLMatrixf.h>
#include <MultiTouchEvents/MultiTouchEventHandler.h>
#include "Finger.h"

using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class RSTObject : 
		public MultiTouchEventHandler
	{
	public:
		RSTObject(bool rotateEnabled = true, bool scaleEnabled = true, bool translateEnabled = true);
		~RSTObject(void);

		void			debugScale			(float z, const Point2f &p);
		virtual bool	contains			(const FingerEventArgs &e) const = 0;
		virtual void	fingerAdded			(const FingerEventArgs &e);
		virtual void	fingerUpdated		(const FingerEventArgs &e);
		virtual void	fingerRemoved		(const FingerEventArgs &e);
		bool			isRotateEnabled		(void) const;
		bool			isScaleEnabled		(void) const;
		bool			isTranslateEnabled	(void) const;
		void			setRotateEnabled	(bool rotateEnabled);
		void			setScaleEnabled		(bool scaleEnabled);
		void			setTranslateEnabled	(bool translateEnabled);

	protected:
		std::map<int, Finger *>	fingers;
		float					scale;
		float					transform[16];

		virtual void	scaleChanged	(void);
		void			translate		(const Vector2f &delta);

	private:
		static const float MAX_SCALE;
		static const float MIN_SCALE;

		bool rotateEnabled;
		bool scaleEnabled;
		bool translateEnabled;
		
		Finger	*findOtherFinger		(unsigned int fId) const;
		void	rst						(const Finger &actuator, const Finger &anchor);
		void	setTransformToIdentity	(void);
		void	translate				(const Finger &actuator);

	};
}

