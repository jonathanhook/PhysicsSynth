/**
 * Class:	Canvas
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <map>
#include <MultiTouchEvents/MultiTouchEventHandler.h>
#include <JDHUtility/Point2i.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/Vector2f.h>
#include "FastDelegate.h"
#include "RSTObject.h"

namespace JDHUtility 
{ 
	class GLMatrixf;
	class GLTexture;
    class GLVbo;
}

using namespace fastdelegate;
using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class MainMenu;
	class ObjectMenu;
	class PhysicsObject;
	class PressAndHold;
	class SettingsMenu;
	class SoundMenu;
	class World;
	class WorldMenu;

	class Canvas :
		public RSTObject
	{
	public:
		typedef FastDelegate0<> SavedCallback;

		Canvas(unsigned int menuWidth);
		~Canvas(void);

		bool					contains		(const FingerEventArgs &e) const;
		void					eraseAllObjects	(void);
		void					eraseAllWorlds	(void);
		void					fingerAdded		(const FingerEventArgs &e);
		void					fingerUpdated	(const FingerEventArgs &e);
		void					fingerRemoved	(const FingerEventArgs &e);
		float					getFps			(void) const;
		std::vector<World *>	getWorlds		(void) const;
		void					loadWorlds		(std::vector<World *> lw);
		void					render			(void);
		MultiTouchEventHandler	*searchEventTree(const FingerEventArgs &e);
		void					setSavedCallback(SavedCallback saved);
		void					update			(void);
		void					updateFps		(float fpsSample);
		void					updatePhysics	(void);

	private:
		enum MenuState { CREATE_WORLD, CREATE_OBJECT, INSPECT_WORLD, INSPECT_OBJECT, SOUNDS, SETTINGS };

		static const float			ADD_DISTANCE_THRESHOLD;
		static const unsigned int	ADD_TIME_THRESHOLD;
		static const unsigned int	FPS_AVERAGE_BUFFER_SIZE;
		static const float			FPS_BORDER;
		static const std::string	FPS_FONT;
		static const float			FPS_HEIGHT;
		static const float			INITIAL_SCALE;
		static const unsigned int	LINE_COUNT;
		static const float			MAX_SCALE;
		static const unsigned int	MENU_MARGIN;
		static const float			SIZE;
		static const std::string	TEXTURE_BACKGROUND;
		static const std::string	TEXTURE_OVERLAY;
		static const unsigned int	TEXTURE_REPEATS;
		static const Point2f		TOOLS_POSITION;
		static const Vector2f		TOOLS_DIMENSIONS;
		static const float			WORLD_DRAG_THRESHOLD;

		GLTexture								*background;
        GLVbo                                   *backgroundVbo;
		float									fps;
		MenuState								lastMenuState;
		MainMenu								*mainMenu;
		Point2f									menuPosition;
		MenuState								menuState;
		unsigned int							menuWidth;
		GLMatrixf								*modelview;
		ObjectMenu								*objectCreateMenu;
		ObjectMenu								*objectInspectMenu;
		GLTexture								*overlay;
        GLVbo                                   *overlayVbo;
		std::map<unsigned int, PressAndHold *>	pressAndHolds;	
		SavedCallback							saved;
		SettingsMenu							*settingsMenu;
		SoundMenu								*soundMenu;
		bool									transformSaved;
		std::vector<World *>					worlds;
		WorldMenu								*worldCreateMenu;
		WorldMenu								*worldInspectMenu;
		bool									worldsDraggable;

		void addWorld							(const Point2f &position);
		void assumeCreateWorldState				(void);
		void assumeCreateObjectState			(void);
		void assumeInspectWorldState			(void);
		void assumeInspectObjectState			(void);
		void assumeSoundsState					(void);
		void assumeSettingsState				(void);
		void constrainTranslate					(void);
		void clearMenus							(void);
		void deselectWorlds						(World *exempt);
		void initMenus							(void);
		void mainMenu_ObjectsSelected			(void);
		void mainMenu_SettingsSelected			(void);
		void mainMenu_SoundsSelected			(void);
		void mainMenu_WorldsSelected			(void);
		void object_Selected					(World *world, PhysicsObject *obj);
		void objectInspectMenu_Erased			(ObjectMenu *sender, PhysicsObject *obj);
		void pressAndHold_Completed				(const PressAndHold &p, const Point2f &pos);
		void removeWorld						(World *world);
		void renderCanvas						(void);
		void renderFps							(void);
		void renderMenus						(void);
		void renderPressAndHolds				(void);
		void renderWorlds						(void);
		void saveTransform						(void);
		void selectObject						(PhysicsObject *object);
		void selectWorld						(World *world);
		void settingsMenu_Saved					(void);
		void updateMenuState					(MenuState menuState);
		void updatePressAndHolds				(void);
		void updateWorlds						(void);
		void world_CreateObjectRequested		(World *world, Point2f position);
		void world_Selected						(World *world);
		void worldInspectMenu_Erased			(void);
	};
}


