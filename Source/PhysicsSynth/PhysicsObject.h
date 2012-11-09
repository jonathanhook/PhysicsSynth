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
#include <MultiTouchEvents/MultiTouchEventHandler.h>
#include <JDHUtility/Point2f.h>
#include <JDHUtility/Vector2f.h>
#include <queue>
#include "FastDelegate.h"
#include "Sounds.h"
#include "SoundEvent.h"

class b2World;
class b2Body;
class b2Joint;

namespace JDHUtility 
{ 
	class Colour3f;
	class Colour4f;
	class GLMatrixf; 
}

using namespace fastdelegate;
using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class FingerJoint;
	class SoundEvent;

	class PhysicsObject : 
		public MultiTouchEventHandler
	{
	public:
		typedef	enum PhysicsObjectType	{ CIRCLE, SQUARE, TRIANGLE, STICK, PARTICLES, BOMB, WHEEL };
	
		typedef FastDelegate2<PhysicsObject *, Point2f>											TranslateCallback;
		typedef FastDelegate1<PhysicsObject *>													SelectedCallback;
		typedef FastDelegate8<SoundConfig *, float, float, float, float, float, float, float>	SoundEventCallback;

		PhysicsObject(	bool		isLocked	= DEFAULT_IS_LOCKED,
						float		size		= DEFAULT_SIZE,
						SoundConfig	*sound		= &Sounds::NO_SOUND,
						float		friction	= DEFAULT_FRICTION,
						float		restitution	= DEFAULT_RESTITUTION);
		~PhysicsObject	(void);

		virtual void				addToWorld				(b2World *world, const Point2f &position);
		virtual void				collide					(b2Body *cb, float cx, float cy);
		virtual bool				contains				(const FingerEventArgs &e) const = 0;
		virtual void				fingerAdded				(const FingerEventArgs &e) = 0;
		virtual void				fingerUpdated			(const FingerEventArgs &e) = 0;
		virtual void				fingerRemoved			(const FingerEventArgs &e) = 0;
		virtual float				getBoundingRegion		(void) const;
		float						getFriction				(void) const;
		bool						getIsLocked				(void) const;
		bool						getIsMarkedForDelete	(void) const;
		bool						getIsSelected			(void) const;
		float						getLastSoundImpulse		(void) const;
		virtual PhysicsObjectType	getObjectType			(void) const = 0;
		virtual const Point2f		&getPosition			(void);
		virtual float				getRenderSize			(void) const;
		float						getRestitution			(void) const;
		float						getSize					(void) const;
		SoundConfig					*getSound				(void) const;
		virtual void				render					(void) = 0;
		virtual void				renderThumbnail			(void) = 0;
		void						selectFromMenu			(void);
		void						setFriction				(float friction);
		virtual void				setPosition				(const Point2f &position);
		void						setRestitution			(float restitution);
		void						setIsLocked				(bool isLocked);
		void						setIsMarkedForDelete	(bool isMarkedForDelete);
		void						setIsSelected			(bool isSelected);
		void						setLastSoundImpulse		(float lastSoundImpulse);
		void						setSelectedCallback		(SelectedCallback selected);
		virtual void				setSize					(float size);
		void						setSound				(SoundConfig *sound);
		void						setSoundEventCallback	(SoundEventCallback soundEvent);
		void						setTranslateCallback	(TranslateCallback translate);
		virtual void				update					(void) = 0;

	protected:
		static const float		DENSITY;
		static const float		DEFAULT_FRICTION;
		static const bool		DEFAULT_IS_LOCKED;
		static const float		DEFAULT_RESTITUTION;
		static const float		DEFAULT_SIZE;
		static const float		MAX_RESTITUTION;
		static const float		MAX_SIZE;
		static const float		MIN_SIZE;
		static const Colour4f	VALUE_COLOUR;

		bool					collided;
		float					cx;
		float					cy;
		std::vector<b2Body *>	bodies;
		float					friction;
		bool					isInWorld;
		bool					isLocked;
		bool					isMarkedForDelete;
		bool					isSelected;
		std::vector<b2Joint *>	joints;
		float					lastSoundImpulse;
		GLMatrixf				*modelview;
		Point2f					position;
		float					restitution;
		SelectedCallback		selected;
		float					size;
		SoundConfig				*sound;
		SoundEventCallback		soundEvent;
		TranslateCallback		translate;
		b2World					*world;

		void				saveTransform		(void);
		virtual void		updateFixtures		(void) = 0;
		virtual void		updateLockedMass	(void) = 0;
	};
}