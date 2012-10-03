/**
 * Class:	DynamicObject
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "PhysicsObject.h"

namespace JDHUtility { class GLTexture; }

namespace PhysicsSynth
{
	class Finger;
	class LoopPointer;

	class DynamicObject :
		public PhysicsObject
	{
	public:
		static const unsigned int PATTERN_LENGTH;

		DynamicObject	(std::string	texturePath,
						float			rate		= DEFAULT_RATE,
						unsigned int	pattern		= DEFAULT_PATTERN,
						float			size		= DEFAULT_SIZE,
						SoundConfig		*sound		= &Sounds::NO_SOUND,
						float			friction	= DEFAULT_FRICTION,
						float			restitution	= DEFAULT_RESTITUTION);
		~DynamicObject	(void);

		virtual void	addToWorld			(b2World *world, const Point2f &position);
		bool			contains			(const FingerEventArgs &e) const;
		void			fingerAdded			(const FingerEventArgs &e);
		void			fingerUpdated		(const FingerEventArgs &e);
		void			fingerRemoved		(const FingerEventArgs &e);
		virtual float	getBoundingRegion	(void) const;
		unsigned int	getPattern			(void) const;
		float			getRate				(void) const;
		virtual void	render				(void);
		void			renderThumbnail		(void);
		virtual void	setPattern			(unsigned int pattern);
		void			setRate				(float rate);
		virtual void	sync				(void);
		virtual void	update				(void);

	protected:
		static const unsigned int	DEFAULT_PATTERN;
		static const float			DEFAULT_RATE;
		static const float			ICON_SIZE;

		LoopPointer		*loop;
		unsigned int	pattern;
		float			rate;

		virtual	void	onPatternTick	(void) = 0;
		void			updateLockedMass(void);

	private:
		static const unsigned int	CIRCLE_VERTICES;
		static const float			THUMBNAIL_SCALE;

		Finger			*finger;
		bool			fingerDown;
		unsigned int	lastTick;
        GLTexture       *texture;
		std::string		texturePath;	

		void renderIcon(void);
	};
}

