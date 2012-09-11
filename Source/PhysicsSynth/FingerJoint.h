/**
 * Class:	FingerJoint
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Colour4f.h>

class b2Body;
class b2MouseJoint;
struct b2Vec2;
class b2World;

namespace JDHUtility { class GLVbo; }
using namespace JDHUtility;

namespace PhysicsSynth
{
	class PhysicsObject;

	class FingerJoint
	{
	public:
		FingerJoint(PhysicsObject *object, b2Body *body, const b2Vec2 &target, b2World *world);
		~FingerJoint(void);

		const b2Body	*getBody	(void) const;
		PhysicsObject	*getObject	(void) const;
		void			render		(void);
		void			updateTarget(const b2Vec2 &target);

	private:
		static const float		END_POINT_SIZE;
		static const Colour4f	VALUE_COLOUR;

		b2Body			*body;
		b2Body			*groundBody;
		b2MouseJoint	*joint;
		PhysicsObject	*object;
		b2World			*world;
        GLVbo           *pointVbo;
        GLVbo           *lineVbo;
		
		void init(const b2Vec2 &target);
	};
}

