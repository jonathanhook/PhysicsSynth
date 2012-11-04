/**
 * Class:	WorldMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include "CircularWorld.h"
#include "ColourPicker.h"
#include "Manager.h"
#include "ObjectPicker.h"
#include "OptionGrid.h"
#include "PhysicsObject.h"
#include "Slider.h"
#include "Sounds.h"
#include "SquareWorld.h"
#include "TargetButton.h"
#include "World.h"
#include "WorldMenu.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const std::string WorldMenu::CIRCLE_WORLD_LABEL = "Circle";
	const std::string WorldMenu::SQUARE_WORLD_LABEL = "Square";
	
	/* Constructors */
	WorldMenu::WorldMenu(const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, (TOP | BOTTOM | LEFT | RIGHT), mode)
	{
		erased = NULL;

		initMenuItems();
	}

	WorldMenu::~WorldMenu(void)
	{
		NDELETE(world);
	}

	/* Public Member Functions */
	World *WorldMenu::createWorld(void)
	{
		assert(world);
	
		World *w = cloneWorld(world->getWorldType());
		return w;
	}

	void WorldMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		if(mode == CREATE)
		{
			std::vector<OptionGrid::Option> options;
			options.push_back(OptionGrid::Option(World::CIRCULAR, CIRCLE_WORLD_LABEL));
			options.push_back(OptionGrid::Option(World::SQUARE, SQUARE_WORLD_LABEL));

			type = new OptionGrid(options, "World Type", position, width);
			type->setSelectionChangedCallback(MakeDelegate(this, &WorldMenu::type_SelectionChanged));
			addMenuItem(*type);
		}

		size = new Slider("Size", position, width);
		size->setValueChangedCallback(MakeDelegate(this, &WorldMenu::size_ValueChanged));
		addMenuItem(*size);

		gravity = new TargetButton("Gravity", position, width);
		gravity->setTargetChangedCallback(MakeDelegate(this, &WorldMenu::gravity_TargetChanged));
		addMenuItem(*gravity);

		if(mode == INSPECT)
		{
			erase = new Button("Erase", position, width);
			erase->setClickedCallback(MakeDelegate(this, &WorldMenu::erase_Clicked));
			addMenuItem(*erase);

			
			objects = new ObjectPicker(position, width);
			objects->setObjectSelectedCallback(MakeDelegate(this, &WorldMenu::objects_ObjectSelected));
			addMenuItem(*objects);
			
		}
	}

	void WorldMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void WorldMenu::setValues(void)
	{
		assert(world);
		assert(gravity);

		gravity->setTargetPosition(world->getGravity());
		size->setValue(world->getSize());

		if(mode == CREATE)
		{
			assert(type);
			type->setSelectedItem(world->getWorldType());
		}
		else
		{
			assert(objects);
			
			int h = dimensions.getY() - objects->getDimensions().getY();
			objects->setWorld(world);
			h += objects->getDimensions().getY();
			dimensions.setY(h);
		}
	}

	void WorldMenu::setWorld(World *world)
	{
		this->world = world;
		setValues();
	}

	/* Private Member Functions */
	World *WorldMenu::cloneWorld(World::WorldType cloneType)
	{
		World *oldWorld = world;
		assert(oldWorld);

		const Point2f		&oldPosition	= oldWorld->getPosition();
		const Vector2f		oldGravity		= oldWorld->getGravity();
		float				oldSize			= oldWorld->getSize();
		unsigned int		worldTrackId	= Manager::getTrackId();

		World *newWorld = NULL;
		if(cloneType == World::CIRCULAR)
		{
			newWorld = new CircularWorld(worldTrackId, oldPosition, oldGravity, oldSize);
		}
		if(cloneType == World::SQUARE)
		{
			newWorld = new SquareWorld(worldTrackId, oldPosition, oldGravity, oldSize);
		}
		assert(newWorld);

		return newWorld;
	}

	void WorldMenu::erase_Clicked(UIElement *sender)
	{
		assert(world);
		unsigned int trackId = world->getTrack();

		world->setIsMarkedForDelete(true);
		world = NULL;

		Manager::clearTrackId(trackId);

		if(erased != NULL)
		{
			erased();
		}
	}

	void WorldMenu::gravity_TargetChanged(const Vector2f &targetPosition)
	{
		assert(world);
		world->setGravity(targetPosition);
	}

	void WorldMenu::objects_ObjectSelected(ObjectPicker *sender, PhysicsObject *obj)
	{
		assert(obj);
		obj->selectFromMenu();
	}

	void WorldMenu::size_ValueChanged(float size)
	{
		assert(world);
		world->setSize(size);
	}

	void WorldMenu::type_SelectionChanged(const OptionGrid::Option &selection)
	{
		if(mode == CREATE)
		{
			// create new world and copy over settings
			World *newWorld = cloneWorld((World::WorldType)selection.id);		

			// delete the old one and point parent's pointer to new one
			NDELETE(world);
			world = newWorld;
		}
		else
		{
			type->setSelectedItem(world->getWorldType());
		}
	}
}
