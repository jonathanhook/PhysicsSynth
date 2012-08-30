/**
 * Class:	PhysicsDebugger
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include "Manager.h"
#include "PhysicsDebugger.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	PhysicsDebugger::CIRCLE_RESOLUTION	= 16;
	const float			PhysicsDebugger::FILL_OPACITY		= 0.5f;

	/* Constructors */
	PhysicsDebugger::PhysicsDebugger(void)
	{
		AppendFlags(e_shapeBit);
		AppendFlags(e_jointBit);
	//	AppendFlags(e_aabbBit);
	//	AppendFlags(e_pairBit);
	//	AppendFlags(e_centerOfMassBit);
	}

	PhysicsDebugger::~PhysicsDebugger(void)
	{
	}

	/* Public Member Functions */
	void PhysicsDebugger::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);

		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(color.r, color.g, color.b, 1.0f);
		glBegin(GL_LINE_LOOP);
			for(unsigned int i = 0; i < (unsigned int)vertexCount; i++)
			{
				const b2Vec2 v = vertices[i];
				float vx = Manager::descale(v.x);
				float vy = Manager::descale(v.y);

				glVertex3f(vx, vy, 0.0f);
			}
		glEnd();

		glPopAttrib();
	}

	void PhysicsDebugger::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);

		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(color.r, color.g, color.b, FILL_OPACITY);
		glBegin(GL_POLYGON);
			for(unsigned int i = 0; i < (unsigned int)vertexCount; i++)
			{
				const b2Vec2 v = vertices[i];
				float vx = Manager::descale(v.x);
				float vy = Manager::descale(v.y);

				glVertex3f(vx, vy, 0.0f);
			}
		glEnd();

		glColor4f(color.r, color.g, color.b, 1.0f);
		glBegin(GL_LINE_LOOP);
			for(unsigned int i = 0; i < (unsigned int)vertexCount; i++)
			{
				const b2Vec2 v = vertices[i];
				float vx = Manager::descale(v.x);
				float vy = Manager::descale(v.y);

				glVertex3f(vx, vy, 0.0f);
			}
		glEnd();

		glPopAttrib();
	}

	void PhysicsDebugger::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color)
	{
		glPushAttrib(GL_TRANSFORM_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		float cx = Manager::descale(center.x);
		float cy = Manager::descale(center.y);
		glTranslatef(cx, cy, 0.0f);

		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(color.r, color.g, color.b, 1.0f);
		glBegin(GL_LINE_LOOP);	
			float sRad = Manager::descale(radius);
			for(unsigned int i = 0; i < CIRCLE_RESOLUTION; i++)
			{
				float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_RESOLUTION) * (float)i; 
				float x		= cos(theta) * sRad;
				float y		= sin(theta) * sRad;

				glVertex3f(x, y, 0.0f);
			}
		glEnd();

		glPopMatrix();
		glPopAttrib();
	}

	void PhysicsDebugger::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)
	{
		glPushAttrib(GL_TRANSFORM_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		float cx = Manager::descale(center.x);
		float cy = Manager::descale(center.y);
		glTranslatef(cx, cy, 0.0f);

		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float sRad = Manager::descale(radius);

		glColor4f(color.r, color.g, color.b, FILL_OPACITY);
		glBegin(GL_POLYGON);
			for(unsigned int i = 0; i < CIRCLE_RESOLUTION; i++)
			{
				float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_RESOLUTION) * (float)i; 
				float x		= cos(theta) * sRad;
				float y		= sin(theta) * sRad;

				glVertex3f(x, y, 0.0f);
			}
		glEnd();

		glColor4f(color.r, color.g, color.b, 1.0f);
		glBegin(GL_LINE_LOOP);
			for(unsigned int i = 0; i < CIRCLE_RESOLUTION; i++)
			{
				float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_RESOLUTION) * (float)i; 
				float x		= cos(theta) * sRad;
				float y		= sin(theta) * sRad;

				glVertex3f(x, y, 0.0f);
			}
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(0.0f,			0.0f,			0.0f);
			glVertex3f(axis.x * sRad,	axis.y * sRad,	0.0f);
		glEnd();

		glPopMatrix();
		glPopAttrib();
	}

	void PhysicsDebugger::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(color.r, color.g, color.b, 1.0f);

		float p1x = Manager::descale(p1.x);
		float p1y = Manager::descale(p1.y);
		float p2x = Manager::descale(p2.x);
		float p2y = Manager::descale(p2.x);

		glBegin(GL_LINE_STRIP);
			glVertex3f(p1x, p1y, 0.0f);
			glVertex3f(p2x, p2y, 0.0f);
		glEnd();

		glPopAttrib();
	}

	void PhysicsDebugger::DrawTransform(const b2Transform &xf)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		b2Vec2 p1 = xf.position, p2;
		const float32 k_axisScale = 0.4f;

		glBegin(GL_LINES);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex3f(p1.x, p1.y, 0.0f);
			p2 = p1 + k_axisScale * xf.R.col1;
			glVertex3f(p2.x, p2.y, 0.0f);

			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glVertex3f(p1.x, p1.y, 0.0f);
			p2 = p1 + k_axisScale * xf.R.col2;
			glVertex3f(p2.x, p2.y, 0.0f);
		glEnd();

		glPopAttrib();
	}
}
