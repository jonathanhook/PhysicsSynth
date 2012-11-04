/**
 * Class:	Canvas
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/DebugTimer.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/GLFontManager.h>
#include <JDHUtility/GLVbo.h>
#include <JDHUtility/WindowingUtils.h>
#include "Canvas.h"
#include "Circle.h"
#include "CircularWorld.h"
#include "MainMenu.h"
#include "ObjectMenu.h"
#include "PressAndHold.h"
#include "SettingsMenu.h"
#include "Sounds.h"
#include "SoundMenu.h"
#include "SquareWorld.h"
#include "WorldMenu.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float			Canvas::ADD_DISTANCE_THRESHOLD	= 0.01f;
	const unsigned int 	Canvas::ADD_TIME_THRESHOLD		= 1000;
	const unsigned int	Canvas::FPS_AVERAGE_BUFFER_SIZE	= 16;
	const float			Canvas::FPS_BORDER				= 0.1f;
	const std::string	Canvas::FPS_FONT				= "Courier New";
	const float			Canvas::FPS_HEIGHT				= 0.015f;
	const float			Canvas::INITIAL_SCALE			= 1.0f;
	const unsigned int	Canvas::LINE_COUNT				= 20;
	const float			Canvas::MAX_SCALE				= 2.5f;
	const unsigned int	Canvas::MENU_MARGIN				= 2;
	//const unsigned int	Canvas::menuWidth				= 256;
	const float			Canvas::SIZE					= 1.0f;
	const std::string	Canvas::TEXTURE_BACKGROUND		= "background.tga";
	const std::string	Canvas::TEXTURE_OVERLAY			= "overlay.tga";
	const unsigned int	Canvas::TEXTURE_REPEATS			= 10;
	const Point2f		Canvas::TOOLS_POSITION			= Point2f(0.0f, 0.0f);
	const Vector2f		Canvas::TOOLS_DIMENSIONS		= Vector2f(0.175f, 0.0f);
	const float			Canvas::WORLD_DRAG_THRESHOLD	= 1.5f;

	/* Constructors */
	Canvas::Canvas(unsigned int menuWidth) :
		RSTObject(false)
	{
		this->menuWidth = menuWidth;

		background			= new GLTexture(TEXTURE_BACKGROUND);
		fps					= 0.0f;
		lastMenuState		= CREATE_WORLD;
		menuPosition		= Point2f(0.0f, 0.0f);
		menuState			= CREATE_WORLD;
		modelview			= new GLMatrixf();
		objectCreateMenu	= NULL;
		objectInspectMenu	= NULL;
		overlay				= new GLTexture(TEXTURE_OVERLAY);
		settingsMenu		= NULL;
		soundMenu			= NULL;
		transformSaved		= false;
		worldCreateMenu		= NULL;
		worldInspectMenu	= NULL;
		worldsDraggable		= true;

        
        GLfloat vertices[12] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, SIZE, 0.0f,
            SIZE, 0.0f, 0.0f,
            SIZE, SIZE, 0.0f
        };
        
        GLfloat uv[8] =
        {
            0.0f,                   0.0f,
            0.0f,                   (float)TEXTURE_REPEATS,
            (float)TEXTURE_REPEATS, 0.0f,
            (float)TEXTURE_REPEATS, (float)TEXTURE_REPEATS
        };
        
        GLfloat overlayUv[8] =
        {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f
        };

        backgroundVbo   = new GLVbo(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, vertices, 4, uv);
        overlayVbo      = new GLVbo(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, vertices, 4, overlayUv);
        
		initMenus();
	}

	Canvas::~Canvas(void)
	{
		NDELETE(background);
		NDELETE(mainMenu);
		NDELETE(modelview);
		NDELETE(objectCreateMenu);
		NDELETE(objectInspectMenu);
		NDELETE(settingsMenu);
		NDELETE(soundMenu);
		NDELETE(worldCreateMenu);
		NDELETE(worldInspectMenu);
	
		std::map<unsigned int, PressAndHold *>::iterator it;
		for(it = pressAndHolds.begin(); it != pressAndHolds.end(); it++)
		{
			NDELETE((*it).second);
		}
		pressAndHolds.clear();

		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			NDELETE(worlds[i]);
		}
		worlds.clear();
	}

	/* Public Member Functions */
	bool Canvas::contains(const FingerEventArgs &e) const
	{
		return true;
	}

	void Canvas::eraseAllObjects(void)
	{
		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *w = worlds[i];
			assert(w != NULL);

			std::vector<PhysicsObject *> objects = w->getObjects();
			for(unsigned int j = 0; j < objects.size(); j++)
			{
				PhysicsObject *o = objects[j];
				assert(o);

				o->setIsMarkedForDelete(true);
			}
		}
	}

	void Canvas::eraseAllWorlds(void)
	{
		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *w = worlds[i];
			assert(w != NULL);
			
			w->setIsMarkedForDelete(true);
		}
	}

	void Canvas::fingerAdded(const FingerEventArgs &e)
	{
		RSTObject::fingerAdded(e);
		
		unsigned int fId	= e.getId();
		PressAndHold *p		= new PressAndHold(e.getPosition(), e.getPosition(), fId);
		pressAndHolds[fId]	= p;

		p->setCompletedCallback(MakeDelegate(this, &Canvas::pressAndHold_Completed));

		selectWorld(NULL);
	}

	void Canvas::fingerUpdated(const FingerEventArgs &e)
	{
		RSTObject::fingerUpdated(e);

		unsigned int fId = e.getId();
		if(pressAndHolds.count(fId) > 0)
		{
			PressAndHold *p = pressAndHolds[fId];
			assert(p);

			p->updateFingerPosition(e.getPosition());
		}
	}
	
	void Canvas::fingerRemoved(const FingerEventArgs &e)
	{
		RSTObject::fingerRemoved(e);

		unsigned int fId = e.getId();
		if(pressAndHolds.count(fId) > 0)
		{
			PressAndHold *p = pressAndHolds[fId];
			assert(p);

			p->setMarkedForDelete(true);
		}
	}

	float Canvas::getFps(void) const
	{
		return fps;
	}

	std::vector<World *> Canvas::getWorlds(void) const
	{
		return worlds;
	}

	void Canvas::loadWorlds(std::vector<World *> lw)
	{
		std::vector<World *>::iterator it;
		for(it = lw.begin(); it != lw.end(); it++)
		{
			World *world = (*it);
			assert(world);

			world->setSelectedCallback(MakeDelegate(this, &Canvas::world_Selected));
			world->setCreateObjectRequestedCallback(MakeDelegate(this, &Canvas::world_CreateObjectRequested));
			world->setObjectSelectedCallback(MakeDelegate(this, &Canvas::object_Selected));

			registerEventHandler(world);
			worlds.push_back(world);
		}
	}

	void Canvas::render(void)
	{
		renderCanvas();
		renderMenus();
		renderPressAndHolds();
		renderFps();
	}

	MultiTouchEventHandler *Canvas::searchEventTree(const FingerEventArgs &e)
	{
		if(enabled)
		{
			// search menus
			for(vector<MultiTouchEventHandler *>::iterator it = handlers.begin(); it != handlers.end(); it++)
			{
				UIElement *menu = dynamic_cast<UIElement *>(*it);
				if(menu)
				{
					MultiTouchEventHandler *handled = (*it)->searchEventTree(e);

					if(handled != NULL) 
					{
						return handled;
					}
				}
			}

			// search physics objects
			for(vector<MultiTouchEventHandler *>::iterator it = handlers.begin(); it != handlers.end(); it++)
			{
				UIElement *menu = dynamic_cast<UIElement *>(*it);
				if(!menu)
				{
					MultiTouchEventHandler *handled = (*it)->searchEventTree(e);

					if(handled != NULL) 
					{
						return handled;
					}
				}
			}

			if(contains(e)) return this;		
		}
		
		return NULL;	
	}

	void Canvas::setSavedCallback(SavedCallback saved)
	{
		this->saved = saved;
	}

	void Canvas::update(void)
	{
		updateWorlds();
		updatePressAndHolds();
		constrainTranslate();
	}

	void Canvas::updateFps(float fpsSample)
	{
		this->fps = fpsSample;
	}

	void Canvas::updatePhysics(void)
	{
		DebugTimer::start("Canvas::updatePhysics");

		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *w = worlds[i];
			assert(w != NULL);

			w->updatePhysics();
		}

		DebugTimer::end("Canvas::updatePhysics");
	}

	/* Private Member Functions */
	void Canvas::addWorld(const Point2f &position)
	{
		assert(modelview);
		assert(worldCreateMenu);

		Point2f p = position;
		modelview->unTranslatePoint(p);
		modelview->unScalePoint(p);

		World *world = worldCreateMenu->createWorld();
		world->setPosition(p);
		world->setSelectedCallback(MakeDelegate(this, &Canvas::world_Selected));
		world->setCreateObjectRequestedCallback(MakeDelegate(this, &Canvas::world_CreateObjectRequested));
		world->setObjectSelectedCallback(MakeDelegate(this, &Canvas::object_Selected));

		registerEventHandler(world);
		worlds.push_back(world);
	}

	void Canvas::assumeCreateWorldState(void)
	{
		assert(mainMenu);
		assert(worldCreateMenu);

		registerEventHandler(worldCreateMenu);
		deselectWorlds(NULL);

		Point2i cePos = worldCreateMenu->getPosition();
		cePos.translateY(worldCreateMenu->getDimensions().getY() + MENU_MARGIN);

		mainMenu->setChecked(MainMenu::WORLDS);
	}

	void Canvas::assumeCreateObjectState(void)
	{
		assert(objectCreateMenu);

		registerEventHandler(objectCreateMenu);
		deselectWorlds(NULL);

		mainMenu->setChecked(MainMenu::OBJECTS);
	}

	void Canvas::assumeInspectWorldState(void)
	{
		registerEventHandler(worldInspectMenu);

		mainMenu->setChecked(MainMenu::WORLDS);
	}

	void Canvas::assumeInspectObjectState(void)
	{
		registerEventHandler(objectInspectMenu);

		mainMenu->setChecked(MainMenu::OBJECTS);
	}

	void Canvas::assumeSoundsState(void)
	{
		assert(soundMenu);
		registerEventHandler(soundMenu);
		soundMenu->setValues();

		deselectWorlds(NULL);
	}

	void Canvas::assumeSettingsState(void)
	{
		assert(settingsMenu);
		registerEventHandler(settingsMenu);

		deselectWorlds(NULL);
	}

	void Canvas::constrainTranslate(void)
	{
		if(transformSaved)
		{
			float xt = 0.0f;
			float yt = 0.0f;
			
			assert(modelview);
			float x = modelview->getXTranslation();
			float y = modelview->getYTranslation();
			float xScale = modelview->getXScale();
			float yScale = modelview->getYScale();

			if(x > 0.0f)
			{
				xt = -x;
			}
			else if((x + xScale) < 1.0f)
			{
				xt = 1.0f - (x + xScale);
			}
		
			if(y > 0.0f)
			{
				yt =-y;
			}
			else if((y + yScale) < 1.0f) 
			{
				yt = 1.0f - (y + yScale);
			}

			translate(Vector2f(xt, yt));
			transformSaved = false;
		}
		
	}

	void Canvas::clearMenus(void)
	{
		unregisterEventHandler(worldCreateMenu);
		unregisterEventHandler(worldInspectMenu);
		unregisterEventHandler(objectCreateMenu);
		unregisterEventHandler(objectInspectMenu);
		unregisterEventHandler(soundMenu);
		unregisterEventHandler(settingsMenu);		
	}

	void Canvas::deselectWorlds(World *exempt)
	{
		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *w = worlds[i];
			assert(w);

			bool worldSelected = (w == exempt);
			w->setSelected(worldSelected);
			w->deselectObjects();
		}
	}

	void Canvas::initMenus(void)
	{
		// main menu
		mainMenu = new MainMenu(Point2i(MENU_MARGIN, MENU_MARGIN), menuWidth);
		mainMenu->setWorldsSelectedCallback(MakeDelegate(this, &Canvas::mainMenu_WorldsSelected));
		mainMenu->setSettingsSelectedCallback(MakeDelegate(this, &Canvas::mainMenu_SettingsSelected));
		mainMenu->setSoundsSelectedCallback(MakeDelegate(this, &Canvas::mainMenu_SoundsSelected));
		mainMenu->setObjectsSelectedCallback(MakeDelegate(this, &Canvas::mainMenu_ObjectsSelected));
		registerEventHandler(mainMenu);

		Point2i wPos = mainMenu->getPosition();
		wPos.translateY(mainMenu->getDimensions().getY() + MENU_MARGIN * 2);
		
		// world menus
		worldCreateMenu	= new WorldMenu(wPos, menuWidth, Menu::CREATE);
		worldCreateMenu->setWorld(new CircularWorld(0));

		worldInspectMenu = new WorldMenu(wPos, menuWidth, Menu::INSPECT);
		worldInspectMenu->setErasedCallback(MakeDelegate(this, &Canvas::worldInspectMenu_Erased));

		// object menus
		objectCreateMenu = new ObjectMenu(wPos, menuWidth, Menu::CREATE);

		objectInspectMenu = new ObjectMenu(wPos, menuWidth, Menu::INSPECT);
		objectInspectMenu->setErasedCallback(MakeDelegate(this, &Canvas::objectInspectMenu_Erased));

		// sound menu
		soundMenu = new SoundMenu(wPos, menuWidth);

		// settings menu
		settingsMenu = new SettingsMenu(wPos, menuWidth);
		settingsMenu->setSavedCallback(MakeDelegate(this, &Canvas::settingsMenu_Saved));

		updateMenuState(CREATE_WORLD);
	}

	void Canvas::mainMenu_ObjectsSelected(void)
	{
		lastMenuState = CREATE_OBJECT;
		updateMenuState(CREATE_OBJECT);
	}

	void Canvas::mainMenu_SettingsSelected(void)
	{
		lastMenuState = SETTINGS;
		updateMenuState(SETTINGS);
	}

	void Canvas::mainMenu_SoundsSelected(void)
	{
		lastMenuState = SOUNDS;
		updateMenuState(SOUNDS);
	}

	void Canvas::mainMenu_WorldsSelected(void)
	{
		lastMenuState = CREATE_WORLD;
		updateMenuState(CREATE_WORLD);
	}

	void Canvas::object_Selected(World *world, PhysicsObject *obj)
	{
		selectObject(obj);
		updateMenuState(INSPECT_OBJECT);
	}

	void Canvas::objectInspectMenu_Erased(ObjectMenu *sender, PhysicsObject *erased)
	{
		updateMenuState(lastMenuState);

		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *w = worlds[i];
			assert(w);

			w->clearFingerJoints(erased);
		}
	}

	void Canvas::pressAndHold_Completed(const PressAndHold &p, const Point2f &pos)
	{
		addWorld(pos);
	}

	void Canvas::removeWorld(World *world)
	{
	}

	void Canvas::renderCanvas(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(transform);
		saveTransform();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // background
        background->bind(GL_REPLACE, GL_NEAREST, GL_LINEAR, GL_REPEAT, GL_REPEAT);
        backgroundVbo->render();
        background->unbind();
    
        // overlay
        overlay->bind(GL_REPLACE, GL_NEAREST, GL_LINEAR, GL_REPEAT, GL_REPEAT);
        overlayVbo->render();
        overlay->unbind();
    
		renderWorlds();
        
        glDisable(GL_BLEND);
		glPopMatrix();
	}

	void Canvas::renderFps(void)
	{
		char buff[16];
		sprintf(buff, "%3.1f", fps);

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);

		Vector2f dims = f->queryBox(GLFontManager::LARGE, buff);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		f->renderString(GLFontManager::LARGE, buff, Point2f(1.0f - (dims.getX() * 1.1f), 0.0));
	}

	void Canvas::renderMenus(void)
	{
		DebugTimer::start("Canvas::renderMenus");

		assert(mainMenu);
		mainMenu->render();

		switch(menuState)
		{
			case CREATE_WORLD:
				assert(worldCreateMenu);
				worldCreateMenu->render();
				break;

			case CREATE_OBJECT:
				assert(objectCreateMenu);
				objectCreateMenu->render();
				break;

			case INSPECT_WORLD:
				assert(worldInspectMenu);
				worldInspectMenu->render();
				break;

			case INSPECT_OBJECT:
				assert(objectInspectMenu);
				objectInspectMenu->render();
				break;

			case SOUNDS:
				assert(soundMenu);
				soundMenu->render();
				break;

			case SETTINGS:
				assert(settingsMenu);
				settingsMenu->render();
				break;
		}

		DebugTimer::end("Canvas::renderMenus");
	}

	void Canvas::renderPressAndHolds(void)
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

		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *world = worlds[i];
			assert(world != NULL);

			world->renderPressAndHolds();
		}
	}

	void Canvas::renderWorlds(void)
	{
		DebugTimer::start("Canvas::renderWorlds");

		for(unsigned int i = 0; i < worlds.size(); i++)
		{
			World *world = worlds[i];
			assert(world != NULL);

			world->render();
		}

		DebugTimer::end("Canvas::renderWorlds");
	}

	void Canvas::saveTransform(void)
	{
		assert(modelview != NULL);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview->getMatrix());

		transformSaved = true;
	}

	void Canvas::selectObject(PhysicsObject *object)
	{
		if(object != NULL)
		{
			assert(objectInspectMenu);
			objectInspectMenu->setObject(object);
		}
		else
		{
			updateMenuState(lastMenuState);
		}
		
		deselectWorlds(NULL);
		object->setIsSelected(true);
	}
	
	void Canvas::selectWorld(World *world)
	{
		if(world != NULL)
		{
			assert(worldInspectMenu);
			worldInspectMenu->setWorld(world);
		}
		else
		{
			updateMenuState(lastMenuState);
		}

		deselectWorlds(world);
	}

	void Canvas::settingsMenu_Saved(void)
	{
		if(saved != NULL)
		{
			saved();
		}
	}

	void Canvas::updateMenuState(MenuState menuState)
	{
		this->menuState = menuState;

		clearMenus();
		switch(menuState)
		{
			case CREATE_WORLD:
				assumeCreateWorldState();
				break;
			case CREATE_OBJECT:
				assumeCreateObjectState();
				break;
			case INSPECT_WORLD:
				assumeInspectWorldState();
				break;
			case INSPECT_OBJECT:
				assumeInspectObjectState();
				break;
			case SOUNDS:
				assumeSoundsState();
				break;
			case SETTINGS:
				assumeSettingsState();
				break;
		}
	}

	void Canvas::updatePressAndHolds(void)
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

	void Canvas::updateWorlds(void)
	{
		DebugTimer::start("Canvas::updateWorlds");

		std::vector<World *>::iterator it;
		for(it = worlds.begin(); it != worlds.end(); )
		{
			World *w = (*it);
			assert(w);

			if(w->getIsMarkedForDelete())
			{
				unregisterEventHandler(w);
				NDELETE(w);

				it = worlds.erase(it);
			}
			else
			{
				w->update();
				it++;
			}
		}

		DebugTimer::end("Canvas::updateWorlds");
	}

	void Canvas::world_CreateObjectRequested(World *world, Point2f position)
	{
		assert(world);

		PhysicsObject *o = objectCreateMenu->createObject();
		world->addObject(o, position);
	}

	void Canvas::world_Selected(World *world)
	{
		selectWorld(world);
		
		if(world != NULL)
		{
			updateMenuState(INSPECT_WORLD);
		}
	}

	void Canvas::worldInspectMenu_Erased(void)
	{
		updateMenuState(lastMenuState);
	}
}
