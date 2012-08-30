/**
 * Class:	World
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Joints/b2MouseJoint.h>
#include <JDHUtility/Colour3f.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Point2f.h>
#include <sstream>
#include "Circle.h"
#include "FingerJoint.h"
#include "Handle.h"
#include "Manager.h"
#include "ParticleEmitter.h"
#include "PhysicsDebugger.h"
#include "PressAndHold.h"
#include "Sounds.h"
#include "FingerQueryCallback.h"
#include "World.h"

using namespace JDHUtility;

namespace PhysicsSynth
{
	/* Public Constants */
	const Vector2f		World::DEFAULT_GRAVITY		= Vector2f(0.0f, 0.0f);
	const Point2f		World::DEFAULT_POSITION		= Point2f(0.0f, 0.0f);
	const float			World::DEFAULT_SIZE			= 0.5f;
	const double		World::UPDATE_RATE			= 0.01667;

	/* Protected Constants */
	const float World::BORDER		= 0.005f;
	const float World::HANDLE_SIZE	= 0.0175f;
	const float World::MAX_SIZE		= 0.125f;
	const float World::MIN_SIZE		= 0.05f;

	/* Private Constants */
	const float			World::ALPHA_MODIFIER			= 0.5f;
	const float			World::BACKGROUND_ALPHA			= 0.15f;
	const float			World::BORDER_ALPHA				= 0.3f;
	const bool			World::DO_SLEEP					= true;
	const float			World::MIN_COLLISION_MASS		= 0.01f;
	const float			World::MAX_CONTACT_IMPULSE		= 100.0f;
	const float			World::MAX_GRAVITY				= 25.0f;
	const float			World::MAX_INERTIA				= 5.0f;
	const float			World::MAX_VELOCITY				= 50.0f;
	const unsigned int	World::POSITION_ITERATIONS		= 2;
	const Colour4f		World::SELECTED_COLOUR			= Colour4f(0.11f, 0.53f, 0.71f, 0.5f);
	const std::string	World::TRACK_FONT				= "Arial";
	const unsigned int	World::VELOCITY_ITERATIONS		= 6;

	/* Constructors */
	World::World(unsigned char track, const Point2f &position, const Vector2f &gravity, float size)
	{
		this->track			= track;
		this->position		= position;
		this->gravity		= gravity;
		this->size			= size;

		backgroundDl			= -1;
		borderDl				= -1;
		createObjectRequested	= NULL;
		finger					= NULL;
		fingerDown				= false;
		glassDl					= -1;
		handleA					= NULL;
		handleB					= NULL;
		isMarkedForDelete		= false;
		last					= ((double)CrossPlatformTime::getTimeMillis()) / 1000.0;
		limitBody				= NULL;
		modelview				= new GLMatrixf();
		objectSelected			= NULL;
		outlineDl				= -1;
		physicsDebugger			= new PhysicsDebugger();
		remainder				= 0.0;
		renderMode				= GRAPHICS;
		selected				= false;
		selectedCallback		= NULL;
		selectedDl				= -1;
		sizeChanged				= false;

		init();
	}

	World::~World(void)
	{
		// Box2D delete
		if(limitBody != NULL)
		{
			world->DestroyBody(limitBody);
			limitBody = NULL;
		}

		// standard delete
		for(unsigned int i = 0; i < limits.size(); i++)
		{
			NDELETE(limits[i]);
		}
		limits.clear();

		std::map<unsigned int, FingerJoint *>::iterator it;
		for(it = fingerJoints.begin(); it != fingerJoints.end(); it++)
		{
			NDELETE((*it).second);
		}
		fingerJoints.clear();

		while(!soundEvents.empty())
		{
			SoundEvent *se = soundEvents.front();
			assert(se);

			soundEvents.pop();
			NDELETE(se);
		}

		NDELETE(handleA);
		NDELETE(handleB);
		NDELETE(physicsDebugger);
		NDELETE(world);
	}

	/* Public Member Functions */
	void World::addObject(PhysicsObject *object, const Point2f &position)
	{
		assert(object);

		Point2f p = Manager::scale(position);
		object->setSelectedCallback(MakeDelegate(this, &World::object_Selected));
		object->setSoundEventCallback(MakeDelegate(this, &World::object_SoundEvent));
		object->setTranslateCallback(MakeDelegate(this, &World::object_Translated));
		object->addToWorld(world, p);

		registerEventHandler(object); 
		objects.push_back(object);

		deselectOtherObjects(NULL);
	}

	void World::deselectObjects(void)
	{
		deselectOtherObjects(NULL);
	}

	void World::clearFingerJoints(PhysicsObject *obj)
	{
		std::map<unsigned int, FingerJoint *>::iterator it;
		for(it = fingerJoints.begin(); it != fingerJoints.end(); )
		{
			FingerJoint *fj = (*it).second;
			assert(fj);


			PhysicsObject *p = fj->getObject();
			assert(p);

			if(obj == p)
			{
				NDELETE(fj);
				//it = fingerJoints.erase(it);
                fingerJoints.erase(it++);
			}
			else
			{
				//it++;
                ++it;
			}

		}
	}

	void World::fingerAdded(const FingerEventArgs &e)
	{
		bool fj = queryFingerJoint(e.getId(), e.getPosition());
	
		if(!fj)
		{
			Point2f cp = e.getPosition();
			assert(modelview);
			modelview->unTranslatePoint(cp);
			modelview->unScalePoint(cp);
			
			unsigned int fId	= e.getId();
			PressAndHold *ph	= new PressAndHold(e.getPosition(), cp, fId);
			pressAndHolds[fId]	= ph;

			ph->setCompletedCallback(MakeDelegate(this, &World::pressAndHold_Completed));

			if(selectedCallback != NULL)
			{
				selectedCallback(NULL);
			}
		}
	}

	void World::fingerUpdated(const FingerEventArgs &e)
	{
		unsigned int id = e.getId();
		if(fingerJoints.count(id) > 0)
		{
			Point2f p = e.getPosition();
			modelview->unTranslatePoint(p);
			modelview->unScalePoint(p);

			FingerJoint *f = fingerJoints[id];
			assert(f);

			float sx = Manager::scale(p.getX());
			float sy = Manager::scale(p.getY());
			f->updateTarget(b2Vec2(sx, sy));
		}
		else if(pressAndHolds.count(id) > 0)
		{
			Point2f p = e.getPosition();
			//modelview->unTranslatePoint(p);
			//modelview->unScalePoint(p);

			PressAndHold *ph = pressAndHolds[id];
			assert(ph);

			ph->updateFingerPosition(p);
		}
		else
		{
			queryFingerJoint(id, e.getPosition());
		}
	}
	
	void World::fingerRemoved(const FingerEventArgs &e)
	{
		unsigned int id = e.getId();
		if(fingerJoints.count(id) > 0)
		{
			FingerJoint *f = fingerJoints[id];
			fingerJoints.erase(id);
			NDELETE(f);
		}

		if(pressAndHolds.count(id) > 0)
		{
			PressAndHold *p = pressAndHolds[id];
			assert(p);

			p->setMarkedForDelete(true);
		}
	}

	bool World::getIsMarkedForDelete(void) const
	{
		return isMarkedForDelete;
	}

	std::vector<PhysicsObject *> World::getObjects(void) const
	{
		return objects;
	}

	const Vector2f &World::getGravity(void) const
	{
		return gravity;
	}

	const Point2f &World::getPosition(void) const
	{
		return position;
	}

	float World::getRenderSize(void) const
	{
		return MIN_SIZE + (size * MAX_SIZE);
	}

	float World::getSize(void) const
	{
		return size;
	}

	unsigned int World::getTrack(void) const
	{
		return track;
	}

	void World::keyPressed(unsigned char key)
	{
		switch(key)
		{
			case '1':
				setRenderMode(GRAPHICS);
				break;
			case '2':
				setRenderMode(BOTH);
				break;
			case '3':
				setRenderMode(DEBUG_RENDER);
				break;
		}
	}

	void World::render(void)
	{	
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(position.getX(), position.getY(), 0.0f);
		saveTransform();		

		if(renderMode == GRAPHICS || renderMode == BOTH)
		{
			renderWorld();
			renderObjects();
		}

		if(renderMode == DEBUG || renderMode == BOTH)
		{
			world->DrawDebugData();
		}

		renderHandles();
		renderFingerJoints();

		glPopMatrix();
	}

	void World::renderPressAndHolds(void)
	{
		std::map<unsigned int, PressAndHold *>::iterator it;
		for(it = pressAndHolds.begin(); it != pressAndHolds.end(); it++)
		{
			PressAndHold *p = (*it).second;
			assert(p);

			if(!p->getMarkedForDelete())
			{
				p->render();
			}
		}
	}

	void World::setCreateObjectRequestedCallback(CreateObjectRequestedCallback createObjectRequested)
	{
		this->createObjectRequested = createObjectRequested;
	}

	void World::setGravity(const Vector2f &gravity)
	{
		assert(world != NULL);

		b2Vec2 b2Gravity(gravity.getX() * MAX_GRAVITY, gravity.getY() * MAX_GRAVITY);
		world->SetGravity(b2Gravity);

		this->gravity = gravity;

		wakeAll();
	}

	void World::setIsMarkedForDelete(bool isMarkedForDelete)
	{
		assert(handleA);
		assert(handleB);

		// HACK: no delete if handles captured
		bool okToDelete = (!handleA->isCaptured() && !handleB->isCaptured());

		this->isMarkedForDelete = (isMarkedForDelete && okToDelete);
	}

	void World::setObjectSelectedCallback(ObjectSelectedCallback objectSelected)
	{
		this->objectSelected = objectSelected;
	}

	void World::setPosition(const Point2f &position)
	{
		this->position = position;
	}

	void World::setRenderMode(RenderMode renderMode)
	{
		this->renderMode = renderMode;
	}

	void World::setSelected(bool selected)
	{
		this->selected = selected;

		if(selected)
		{
			deselectOtherObjects(NULL);
		}
	}

	void World::setSelectedCallback(SelectedCallback selectedCallback)
	{
		this->selectedCallback = selectedCallback;
	}

	void World::setSize(float size)
	{
		this->size = size;

		// go through all objects, if there bounding sphere is less than new size
		// put them in the middle and limit the new size to their bounding sphere
		for(unsigned int i = 0; i < objects.size(); i++)
		{
			PhysicsObject *p = objects[i];
			assert(p);

			object_Translated(p, p->getPosition());
		}

		updateSize();
	}

	void World::update(void)
	{
		// update objects

		std::vector<PhysicsObject *>::iterator it;
		for(it = objects.begin(); it != objects.end(); )
		{
			PhysicsObject *o = (*it);
			assert(o);

			if(o->getIsMarkedForDelete())
			{
				clearFingerJoints(o);
				unregisterEventHandler(o);
				it = objects.erase(it);

				NDELETE(o);
			}
			else
			{
				o->update();
				it++;
			}
		}

		// send events
		while(!soundEvents.empty())
		{
			SoundEvent *se = soundEvents.front();
			assert(se);

            // TODO: MAC FIX
			//se->send();

			soundEvents.pop();
			NDELETE(se);
		}

		updatePressAndHolds();
	}

	void World::updatePhysics(void)
	{
		double now		= ((double)CrossPlatformTime::getTimeMillis()) / 1000.0;
		double elapsed	= now - last;
		remainder += elapsed;
 
		while(remainder >= UPDATE_RATE)
		{
			remainder -= UPDATE_RATE;
			world->Step(UPDATE_RATE, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

			if(sizeChanged)
			{
				checkObjectsContained();
				sizeChanged = false;
			}
		}

		last = now;
	}

	/* Protected Member Functions */
	void World::handle_Dragged(Handle *h, const Vector2f &delta)
	{
		position.translate(delta);

		if(selectedCallback != NULL)
		{
			selectedCallback(this);
		}
	}

	void World::handle_Pressed(Handle *h)
	{
		if(selectedCallback != NULL)
		{
			selectedCallback(this);
		}
	}

	void World::saveTransform(void)
	{
		assert(modelview != NULL);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview->getMatrix());
	}

	void World::setupLimits(void)
	{
		if(limitBody != NULL)
		{
			world->DestroyBody(limitBody);
		}

		b2BodyDef bd;
		limitBody = world->CreateBody(&bd);
		//limitBody->SetUserData((World *)this);

		b2PolygonShape shape;

		unsigned int limitsSize = limits.size();
		for(unsigned int i = 0; i < limitsSize; i++)
		{
			Point2f *start	= limits[(i - 1) % limitsSize];
			Point2f *end	= limits[i];

			Point2f ss = Manager::scale(*start);
			Point2f se = Manager::scale(*end);

			assert(start != NULL);
			assert(end != NULL);
			
			shape.SetAsEdge(b2Vec2(ss.getX(), ss.getY()), b2Vec2(se.getX(), se.getY()));
			
			b2FixtureDef fixtureDef;
			fixtureDef.shape		= &shape;	
			fixtureDef.density		= 0.0f;
			limitBody->CreateFixture(&fixtureDef);
		}
	}

	/* Private Member Functions */
	void World::checkObjectsContained(void)
	{
		for(unsigned int i = 0; i < objects.size(); i++)
		{
			PhysicsObject *o = objects[i];
			assert(o);

			const Point2f &objPos = o->getPosition();
			if(!contains(objPos))
			{
				o->setPosition(Point2f(0.0f, 0.0f));
			}
		}
	}

	void World::deselectOtherObjects(PhysicsObject *exempt)
	{
		for(unsigned int i = 0; i < objects.size(); i++)
		{
			PhysicsObject *o = objects[i];
			assert(o);

			bool objSelected = (o == exempt);
			o->setIsSelected(objSelected);
		}
	}

	void World::init(void)
	{
		b2Vec2 b2Gravity(gravity.getX(), gravity.getY());
		world = new b2World(b2Gravity, DO_SLEEP);
		world->SetDebugDraw(physicsDebugger);
		world->SetContactListener(this);
	}

	void World::object_Selected(PhysicsObject *obj)
	{
		if(objectSelected != NULL)
		{
			objectSelected(this, obj);
		}

		deselectOtherObjects(obj);
	}

	void World::object_SoundEvent(SoundConfig *sound, float x, float y, float angle, float velocity, float spin, float inertia, float contactImpulse)
	{
		assert(sound);

		float renderSize	= Manager::scale(getRenderSize());				
		float positionX		= (x / (renderSize * 2.0f)) + 0.5f;
		float positionY		= (y / (renderSize * 2.0f)) + 0.5f;

		soundEvents.push(sound->getSoundEvent(track, positionX, positionY, angle, velocity, spin, inertia, contactImpulse));
	}

	void World::object_Translated(PhysicsObject *obj, Point2f fPos)
	{
		assert(obj);

		limitTranslate(fPos, obj->getBoundingRegion());	
		obj->setPosition(fPos);
	}

	void World::pressAndHold_Completed(const PressAndHold &p, const Point2f &pos)
	{
		if(createObjectRequested != NULL)
		{
			createObjectRequested(this, pos);
		}
	}

	void World::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
	{
		b2Fixture *a = contact->GetFixtureA();
		b2Fixture *b = contact->GetFixtureB();

		processCollision(a, impulse);
		processCollision(b, impulse);
	}

	void World::processCollision(b2Fixture *fixture, const b2ContactImpulse *impulse)
	{
		assert(impulse);
		assert(fixture);

		b2Body *body = fixture->GetBody();
		assert(body);
		
		void *userData = body->GetUserData();
		if(userData != NULL)
		{
			PhysicsObject *po			= (PhysicsObject *)userData;
			const SoundConfig *sound	= po->getSound();
			
			float renderSize		= Manager::scale(getRenderSize());				
			float positionX			= (body->GetPosition().x / (renderSize * 2.0f)) + 0.5f;
			float positionY			= (body->GetPosition().y / (renderSize * 2.0f)) + 0.5f;
			float angle				= fabs(fmodf(body->GetAngle(), (float)M_PI * 2.0f) / ((float)M_PI * 2.0f));	
			
			float vx		= fabs(body->GetLinearVelocity().x / MAX_VELOCITY);
			float vy		= fabs(body->GetLinearVelocity().y / MAX_VELOCITY);
			float velocity	= sqrt((vx * vx) + (vy * vy));
			if(velocity > 1.0f) 
			{
				velocity = 1.0f;
			}

			float spin = fabs(body->GetAngularVelocity() / MAX_VELOCITY);
			if(spin > 1.0f)
			{
				spin = 1.0f;
			}

			float inertia = body->GetInertia() / MAX_INERTIA;
			if(inertia > 1.0f)
			{
				inertia = 1.0f;
			}

			float contactImpulse	= impulse->normalImpulses[0] / MAX_CONTACT_IMPULSE;
			if(contactImpulse > 1.0f)
			{
				contactImpulse = 1.0f;
			}

			float mass = body->GetMass();
			if(mass != 0.0f && (contactImpulse / mass) > MIN_COLLISION_MASS)
			{
				SoundEvent *se = sound->getSoundEvent(track, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
				soundEvents.push(se);
			}
		}
	}

	bool World::queryFingerJoint(unsigned int id, const Point2f &position)
	{
		assert(modelview);
		
		Point2f fp = position;
		modelview->unTranslatePoint(fp);
		modelview->unScalePoint(fp);

		float sx = Manager::scale(fp.getX());
		float sy = Manager::scale(fp.getY());
		float fs = Manager::scale(Manager::FINGER_SIZE / modelview->getXScale());
		b2Vec2 p(sx, sy);

		// Make a small box
		b2AABB aabb;
		b2Vec2 d;
		d.Set(fs, fs);
		aabb.lowerBound = p - d;
		aabb.upperBound = p + d;

		// Query the world for overlapping shapes
		FingerQueryCallback callback(p, fs);
		world->QueryAABB(&callback, aabb);

		if (callback.hasFixture())
		{
			b2Fixture		&fixture		= callback.getFixture();
			const b2Vec2	&collisionPoint	= callback.getCollisionPoint();

			b2Body* body = fixture.GetBody();
			assert(body);

			PhysicsObject *pObj = (PhysicsObject *)body->GetUserData();
			object_Selected(pObj);

			FingerJoint *f = new FingerJoint(pObj, body, collisionPoint, world);
			fingerJoints[id] = f;

			return true;
		}
		else	
		{
			return false;
		}
	}

	void World::renderHandles(void)
	{
		assert(handleA);
		handleA->render();

		assert(handleB);
		handleB->render();
	}

	void World::renderFingerJoints(void)
	{
		std::map<unsigned int, FingerJoint *>::iterator it;
		for(it = fingerJoints.begin(); it != fingerJoints.end(); it++)
		{
			FingerJoint *fj = (*it).second;
			assert(fj);

			fj->render();
		}
	}

	void World::renderObjects(void)
	{
		for(unsigned int i = 0; i < objects.size(); i++)
		{
			PhysicsObject *o = objects[i];
			assert(o != NULL);

			o->render();
		}
	}

	void World::renderWorld(void)
	{
		float alphaModifier = fingerDown ? ALPHA_MODIFIER : 1.0f;

		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		if(selected)
		{
			SELECTED_COLOUR.use();
			glLineWidth(2.0f);
		}
		else
		{
			glColor4f(1.0f, 1.0f, 1.0f, alphaModifier);
			glLineWidth(1.0f);
		}
		
		if(outlineDl == -1)
		{
			outlineDl = glGenLists(1);
			glNewList(outlineDl, GL_COMPILE);

			glBegin(GL_LINES);
				unsigned int limitsSize = limits.size();
				for(unsigned int i = 0; i < limitsSize; i++)
				{
					Point2f *p0 = limits[i];	
					assert(p0 != NULL);

					Point2f *p1 = limits[(i + 1) % limitsSize];	
					assert(p1 != NULL);

					// innner
					float ix0 = p0->getX();
					float iy0 = p0->getY();
					glVertex3f(ix0, iy0, 0.0f);

					float ix1 = p1->getX();
					float iy1 = p1->getY();
					glVertex3f(ix1, iy1, 0.0f);
					
					// outer
					Vector2f v0(ix0, iy0);
					float magnitude0	= v0.getMagnitude();
					float d0			= 1.0f + (BORDER / magnitude0);

					float ox0 = p0->getX() * d0;
					float oy0 = p0->getY() * d0;
					glVertex3f(ox0, oy0, 0.0f);

					Vector2f v1(ix1, iy1);
					float magnitude1	= v1.getMagnitude();
					float d1			= 1.0f + (BORDER / magnitude1);

					float ox1 = p1->getX() * d1;
					float oy1 = p1->getY() * d1;
					glVertex3f(ox1, oy1, 0.0f);
				}
			glEnd();

			glEndList();
		}
		glCallList(outlineDl);

		glColor4f(1.0f, 1.0f, 1.0f, BACKGROUND_ALPHA * alphaModifier);
		if(backgroundDl == -1)
		{
			backgroundDl = glGenLists(1);
			glNewList(backgroundDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);	
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_POLYGON);
				unsigned int limitsSize = limits.size();
				for(unsigned int i = 0; i <= limitsSize; i++)
				{
					Point2f *p = limits[i % limitsSize];	
					assert(p != NULL);

					float x = p->getX();
					float y = p->getY();

					glVertex3f(x, y, 0.0f);
				}
			glEnd();

			glPopAttrib();
			glEndList();
		}
		glCallList(backgroundDl);

		// TODO: can this be in DL now?
		glColor4f(1.0f, 1.0f, 1.0f, BORDER_ALPHA * alphaModifier);
		if(borderDl == -1)
		{
			borderDl = glGenLists(1);
			glNewList(borderDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);	
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_QUAD_STRIP);
				unsigned int limitsSize = limits.size();
				for(unsigned int i = 0; i <= limitsSize; i++)
				{
					Point2f *p = limits[i % limitsSize];	
					assert(p != NULL);

					// inner
					float px0 = p->getX();
					float py0 = p->getY();
					glVertex3f(px0, py0, 0.0f);

					// outer
					Vector2f v(px0, py0);
					float magnitude	= v.getMagnitude();
					float d			= 1.0f + (BORDER / magnitude);

					float px1 = p->getX() * d;
					float py1 = p->getY() * d;
					glVertex3f(px1, py1, 0.0f);
				}
			glEnd();

			glPopAttrib(); // GL_ENABLE_BIT
			glEndList();
		}
		glCallList(borderDl);

		/*
		GLFontManager *fm = GLFontManager::getInstance();
		assert(fm);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(-0.025f, -0.015f, 0.0f);
		glColor4f(1.0, 1.0f, 1.0f, 0.1f);

		char t[3];
		sprintf(t, "%d", track);

		fm->renderString(TRACK_FONT, t, Vector2f(0.05f, 0.05f));
		*/
		//glPopMatrix();

		glPopAttrib(); // GL_CURRENT_BIT | GL_LINE_BIT | GL_ENABLE_BIT
	}

	void World::updatePressAndHolds(void)
	{
		std::map<unsigned int, PressAndHold *>::iterator it;
		for(it = pressAndHolds.begin(); it != pressAndHolds.end(); )
		{
			PressAndHold *p = (*it).second;
			assert(p);

			if(p->getMarkedForDelete())
			{
				NDELETE(p);
				//it = pressAndHolds.erase(it);
                pressAndHolds.erase(it++);
			}
			else
			{
				p->update();
				++it;
			}
		}
	}

	void World::updateSize(void)
	{
		for(unsigned int i = 0; i < limits.size(); i++)
		{
			Point2f *p = limits[i];
			assert(p);

			NDELETE(p);
		}
		limits.clear();

		initLimits();
		setupLimits();
		initHandles();

		backgroundDl	= -1;
		borderDl		= -1;
		outlineDl		= -1;

		sizeChanged = true;
	}

	void World::wakeAll(void)
	{
		assert(world);

		b2Body *body = world->GetBodyList();
		
		while(body != NULL)
		{
			body->SetAwake(true);
			body = body->GetNext();
		}
	}
}
