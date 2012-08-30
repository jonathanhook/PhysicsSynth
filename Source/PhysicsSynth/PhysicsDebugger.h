/**
 * Class:	PhysicsDebugger
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <Box2D/Dynamics/b2World.h>

namespace PhysicsSynth
{
	class PhysicsDebugger :
		public b2DebugDraw
	{
	public:
		PhysicsDebugger(void);
		~PhysicsDebugger(void);

		void DrawPolygon		(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
		void DrawSolidPolygon	(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
		void DrawCircle			(const b2Vec2 &center, float32 radius, const b2Color &color);
		void DrawSolidCircle	(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
		void DrawSegment		(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
		void DrawTransform		(const b2Transform &xf);

	private:
		static const unsigned int	CIRCLE_RESOLUTION;
		static const float			FILL_OPACITY;
	};
}

