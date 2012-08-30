/**
 * Class:	Manager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _SHOW_FINGERS
#define _USE_MATH_DEFINES
#include <assert.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Vector2f.h>
#include "Canvas.h"
#include "Manager.h"
#include "PersistenceManager.h"
#include "World.h"

namespace PhysicsSynth
{
	/* Public Constants */
	const float Manager::FINGER_SIZE = 0.0175f;
	const float Manager::WORLD_SCALE = 50.0f;

	/* Private Constants */
	const unsigned int	Manager::CIRCLE_SEGS		= 16;
	const unsigned int	Manager::FRAME_SAMPLE_COUNT = 5;
	const unsigned int	Manager::MAX_WORLDS			= 8;
	const unsigned int	Manager::MENU_WIDTH			= 4;
	const float			Manager::OPACITY			= 0.33f;
	const std::string	Manager::SAVE_FILE			= "save.csv";

	/* Private Static Variables */
	OSCSender		*Manager::oscSender = NULL;
	unsigned char	Manager::trackIds	= 0;

	/* Public Static Functions */
	void Manager::clearTrackId(unsigned char deletedId)
	{
		trackIds ^= (1 << (deletedId -1));
	}

	Point2f	Manager::descale(const Point2f &p)
	{
		return Point2f(p.getX() / WORLD_SCALE, p.getY() / WORLD_SCALE);
	}

	float Manager::descale(float f)
	{
		return (f / WORLD_SCALE);
	}

	Vector2f Manager::descale(const Vector2f &v)
	{
		return Vector2f(v.getX() / WORLD_SCALE, v.getY() / WORLD_SCALE);
	}

	OSCSender *Manager::getOscSender(void)
	{
		return oscSender;
	}

	unsigned char Manager::getTrackId(void)
	{ 
		for(unsigned i = 0; i < MAX_WORLDS; i++)
		{
			unsigned int mask = 1 << i;
			if(!(trackIds & mask))
			{
				trackIds ^= mask;
				return i + 1;
			}
		}

		return 0;
	}

	Point2f Manager::scale(const Point2f &p)
	{
		return Point2f(p.getX() * WORLD_SCALE, p.getY() * WORLD_SCALE);
	}

	float Manager::scale(float f)
	{
		return (f * WORLD_SCALE);
	}

	Vector2f Manager::scale(const Vector2f &v)
	{
		return Vector2f(v.getX() * WORLD_SCALE, v.getY() * WORLD_SCALE);
	}

	void Manager::setOscSender(OSCSender *sender)
	{
		Manager::oscSender = sender;
	}

	void Manager::setTrackId(unsigned char toSet)
	{
		trackIds ^= (1 << (toSet -1));
	}

	/* Constructors */
	Manager::Manager(unsigned int width, bool dispatchEvents) :
		MultiTouchEventManager(dispatchEvents)
	{
		this->width = width;

		canvas		= new Canvas(width / MENU_WIDTH);
		fingerDl	= 0;
		frames		= 0;
		lastRender	= CrossPlatformTime::getTimeMillis();

		canvas->setSavedCallback(MakeDelegate(this, &Manager::canvas_Saved));

		registerEventHandler(canvas);
	}

	Manager::~Manager(void)
	{
		std::map<unsigned int, Finger *>::iterator it;
		for(it = fingers.begin(); it != fingers.end(); it++)
		{
			NDELETE((*it).second);
		}
		fingers.clear();

		NDELETE(canvas);
	}

	/* Public Member Functions */
	void Manager::load(void)
	{
		std::vector<World *> worlds = PersistenceManager::load(SAVE_FILE);

		assert(canvas);
		canvas->loadWorlds(worlds);
	}

	void Manager::eraseAllObjects(void)
	{
		assert(canvas);
		canvas->eraseAllObjects();
	}

	void Manager::eraseAllWorlds(void)
	{
		assert(canvas);
		canvas->eraseAllWorlds();
	}

	void Manager::render(void)
	{
		assert(canvas);
		canvas->render();
		renderFingers();

		// sample every 10 to get around low precision timer
		if(++frames % FRAME_SAMPLE_COUNT == 0)
		{
			unsigned int now		= CrossPlatformTime::getTimeMillis();
			unsigned int elapsed	= (now - lastRender) / FRAME_SAMPLE_COUNT;
			lastRender = now;

			if(elapsed > 0)
			{
				float fps = 1000.0f / (float)elapsed;
			
				assert(canvas);
				canvas->updateFps(fps);
			}
		}
	}

	void Manager::save(void)
	{
		assert(canvas);
		std::vector<World *> worlds = canvas->getWorlds();
		PersistenceManager::save(SAVE_FILE, worlds);
	}

	void Manager::update(void)
	{
		dispatchAllEvents();

		canvas->update();
		canvas->updatePhysics();
	}

	void Manager::zoom(float z, const Point2f &p)
	{
		assert(canvas);
		canvas->debugScale(z, p);
	}

	/* Private Member Functions */
	void Manager::canvas_Saved(void)
	{
		save();
	}

	void Manager::peek(const FingerEventArgs &e)
	{
#ifdef _SHOW_FINGERS	
		FingerEventArgs::EventType t	= e.getType();
		unsigned int id					= e.getId();

		if(fingers.count(id) == 0 && t == FingerEventArgs::FINGER_ADDED)
		{
			Finger *f = new Finger(id, e.getPosition());
			fingers[id] = f;
		}
		else if(fingers.count(id) == 1 && t == FingerEventArgs::FINGER_UPDATED)
		{
			Finger *f = fingers[id];
			assert(f);

			f->updatePosition(e.getPosition());
		}
		else if(fingers.count(id) == 1 && t == FingerEventArgs::FINGER_REMOVED)
		{
			Finger *f = fingers[id];
			fingers.erase(id);
			NDELETE(f);
		}
#endif
	}

	void Manager::renderFingers(void)
	{
#ifdef _SHOW_FINGERS
		std::map<unsigned int, Finger *>::iterator it;
		for(it = fingers.begin(); it != fingers.end(); it++)
		{
			Finger *f = (*it).second;
			assert(f);

			float x = f->getPosition().getX();
			float y	= f->getPosition().getY();

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(x, y, 0.0f);

			if(!fingerDl)
			{
				fingerDl = glGenLists(1);
				glNewList(fingerDl, GL_COMPILE);

				glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
				glEnable(GL_BLEND);
				glEnable(GL_LINE_SMOOTH);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(1.0f, 1.0f, 1.0f, OPACITY);

				glBegin(GL_LINE_STRIP);
					for(unsigned int i = 0; i <= CIRCLE_SEGS; i++)
					{
						float theta = ((2.0f * (float)M_PI) / (float)CIRCLE_SEGS) * (float)i; 
						float ix = cos(theta) * FINGER_SIZE;
						float iy = sin(theta) * FINGER_SIZE;

						glVertex3f(ix, iy, 0.0f);
					}
				glEnd();

				glPopAttrib();
				glEndList();
			}
			glCallList(fingerDl);

			glPopMatrix();
		}
#endif
	}
}