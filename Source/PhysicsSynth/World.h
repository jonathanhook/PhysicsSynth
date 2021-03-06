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
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <map>
#include <JDHUtility/Point2f.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/Vector2f.h>
#include "FastDelegate.h"
#include "RSTObject.h"

class b2Body;
class b2World;

namespace JDHUtility 
{ 
	class GLMatrixf; 
	class GLTexture;
    class GLVbo;
	class Colour3f;
	class Colour4f;
}

using namespace fastdelegate;
using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class Finger;
	class FingerJoint;
	class Handle;
	class PhysicsDebugger;
	class PhysicsObject;
	class PressAndHold;
	class SoundConfig;
	class SoundEvent;

	class World :
		public MultiTouchEventHandler, public b2ContactListener
	{
	public:
		enum RenderMode { GRAPHICS, DEBUG_RENDER, BOTH };
		enum WorldType	{ CIRCULAR, SQUARE }; 

		typedef FastDelegate2<World *, Point2f>			CreateObjectRequestedCallback;
		typedef FastDelegate2<World *, PhysicsObject *>	ObjectSelectedCallback;
		typedef FastDelegate1<World *>					SelectedCallback;

		static const Vector2f		DEFAULT_GRAVITY;
		static const Point2f		DEFAULT_POSITION;
		static const float			DEFAULT_SIZE;
		static const double			UPDATE_RATE;
		
		World(	unsigned char		track,
				const Point2f		&position		= DEFAULT_POSITION, 
				const Vector2f		&gravity		= DEFAULT_GRAVITY, 
				float				size			= DEFAULT_SIZE);
		~World(	void);

		void							addObject						(PhysicsObject *object, const Point2f &position);
		virtual bool					contains						(const FingerEventArgs &e) const = 0;
		void							deselectObjects					(void);
		void							clearFingerJoints				(PhysicsObject *obj);
		void							fingerAdded						(const FingerEventArgs &e);
		void							fingerUpdated					(const FingerEventArgs &e);
		void							fingerRemoved					(const FingerEventArgs &e);
		const Vector2f					&getGravity						(void) const;
		bool							getIsMarkedForDelete			(void) const;
		std::vector<PhysicsObject *>	getObjects						(void) const;
		const Point2f					&getPosition					(void) const;
		float							getRenderSize					(void) const;
		float							getSize							(void) const;
		unsigned int					getTrack						(void) const;
		virtual WorldType				getWorldType					(void) const = 0;
		unsigned int					getUpdateRateMs					(void) const;
		bool							isDraggable						(void) const;
		void							keyPressed						(unsigned char key);
		void							render							(void);
		void							renderPressAndHolds				(void);
		void							setCreateObjectRequestedCallback(CreateObjectRequestedCallback createObjectRequested);
		void							setGravity						(const Vector2f &gravity);
		void							setIsMarkedForDelete			(bool isMarkedForDelete);
		void							setObjectSelectedCallback		(ObjectSelectedCallback objectSelected);
		void							setPosition						(const Point2f &position);
		void							setRenderMode					(RenderMode renderMode);
		void							setSelected						(bool selected);
		void							setSize							(float size);
		void							setSelectedCallback				(SelectedCallback selectedCallback);
		void							setUpdateRateMs					(unsigned int updateRateMs);
		void							update							(void);
		void							updatePhysics					(void);

	protected:
		static const float BORDER;
		static const float HANDLE_SIZE;
		static const float MAX_SIZE;
		static const float MIN_SIZE;

		Handle					*handleA;
		Handle					*handleB;
		std::vector<Point2f *>	limits;
		GLMatrixf				*modelview;
		Point2f					position;
		float					size;

		virtual bool	contains		(const Point2f &p) const = 0;
		void			handle_Dragged	(Handle *h, const Vector2f &delta); 
		void			handle_Pressed	(Handle *h);
		virtual void	initLimits		(void) = 0;
		virtual void	initHandles		(void) = 0;
		virtual void	limitTranslate	(Point2f &pos, float boundingRadius) = 0;
		void			saveTransform	(void);
		void			setupLimits		(void);

	private:
		static const float			ALPHA_MODIFIER;
		static const float			BACKGROUND_ALPHA;
		static const float			BORDER_ALPHA;
		static const bool			DO_SLEEP;
		static const std::string	GLASS_TEXTURE;
		static const float			MAX_CONTACT_IMPULSE;
		static const float			MAX_GRAVITY;
		static const float			MAX_INERTIA;
		static const float			MAX_VELOCITY;
		static const float			MIN_COLLISION_MASS;
		static const unsigned int	POSITION_ITERATIONS;
		static const Colour4f		SELECTED_COLOUR;
		static const std::string	TRACK_FONT;
		static const unsigned int	VELOCITY_ITERATIONS;
		
		CreateObjectRequestedCallback			createObjectRequested;
		Finger									*finger;
		bool									fingerDown;
		std::map<unsigned int, FingerJoint *>	fingerJoints;
		unsigned int							glassDl;
		Vector2f								gravity;
		bool									isMarkedForDelete;
		double									last;
		b2Body									*limitBody;
		std::vector<PhysicsObject *>			objects;
		ObjectSelectedCallback					objectSelected;
		PhysicsDebugger							*physicsDebugger;
		std::map<unsigned int, PressAndHold *>	pressAndHolds;
		double									remainder;
		RenderMode								renderMode;
		bool									selected;
		SelectedCallback						selectedCallback;
		unsigned int							selectedDl;
		bool									sizeChanged;
		std::queue<SoundEvent *>				soundEvents;
		unsigned char							track;
		b2World									*world;
        GLVbo                                   *outlineVbo;
        GLVbo                                   *backgroundVbo;
        GLVbo                                   *borderVbo;
		
		void checkObjectsContained			(void);
		void deselectOtherObjects			(PhysicsObject *exempt);
		void init							(void);
		void object_Selected				(PhysicsObject *obj);
		void object_SoundEvent				(SoundConfig *sound, float x, float y, float angle, float velocity, float spin, float inertia, float contactImpulse);
		void object_Translated				(PhysicsObject *obj, Point2f fPos);
		void pressAndHold_Completed			(const PressAndHold &p, const Point2f &pos);
		void PostSolve 						(b2Contact *contact, const b2ContactImpulse *impulse);
		void processCollision				(b2Fixture *fixture, const b2ContactImpulse *impulse);
		bool queryFingerJoint				(unsigned int id, const Point2f &position);
		void renderHandles					(void);
		void renderFingerJoints				(void);
		void renderObjects					(void);
		void renderWorld					(void);
		void updatePressAndHolds			(void);
		void updateSize						(void);
        void updateVertices                 (void);
		void wakeAll						(void);
	};
}

