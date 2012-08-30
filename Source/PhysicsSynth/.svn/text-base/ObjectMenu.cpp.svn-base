/**
 * Class:	ObjectMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Point2f.h>
#include "Bomb.h"
#include "BombMenu.h"
#include "Circle.h"
#include "ObjectMenu.h"
#include "OptionGrid.h"
#include "OptionGridItem.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterMenu.h"
#include "PhysicsObject.h"
#include "SimpleObjectMenu.h"
#include "Square.h"
#include "Triangle.h"
#include "Wheel.h"
#include "WheelMenu.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const PhysicsObject::PhysicsObjectType ObjectMenu::DEFAULT_STATE = PhysicsObject::CIRCLE;

	/* Constructors */
	ObjectMenu::ObjectMenu(const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, TOP | LEFT | RIGHT, mode)
	{
		state = DEFAULT_STATE;

		initMenuItems();
		setValues();
	}

	ObjectMenu::~ObjectMenu(void)
	{
		NDELETE(circleMenu);
		NDELETE(particleEmitterMenu);
		NDELETE(squareMenu);
		NDELETE(triangleMenu);
		NDELETE(bombMenu);
		NDELETE(wheelMenu);
	}
	
	/* Public Member Functions */
	PhysicsObject *ObjectMenu::createObject(void) const
	{
		switch(state)
		{
			case PhysicsObject::CIRCLE:
				assert(circleMenu);
				return circleMenu->createObject();

			case PhysicsObject::SQUARE:
				assert(squareMenu);
				return squareMenu->createObject();

			case PhysicsObject::TRIANGLE:
				assert(triangleMenu);
				return triangleMenu->createObject();

			case PhysicsObject::PARTICLES:
				assert(particleEmitterMenu);
				return particleEmitterMenu->createObject();

			case PhysicsObject::BOMB:
				assert(bombMenu);
				return bombMenu->createObject();

			case PhysicsObject::WHEEL:
				assert(wheelMenu);
				return wheelMenu->createObject();

			default:
				assert(false);
				break;
		}

		return NULL;
	}

	void ObjectMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		Point2i subMenuPos = position;

		if(mode == CREATE)
		{
			std::vector<OptionGrid::Option> options;
			options.push_back(OptionGrid::Option(PhysicsObject::CIRCLE, "Circle"));
			options.push_back(OptionGrid::Option(PhysicsObject::SQUARE, "Square"));
			options.push_back(OptionGrid::Option(PhysicsObject::TRIANGLE, "Triangle"));
			options.push_back(OptionGrid::Option(PhysicsObject::PARTICLES, "Particles"));
			options.push_back(OptionGrid::Option(PhysicsObject::BOMB, "Bomb"));
			options.push_back(OptionGrid::Option(PhysicsObject::WHEEL, "Wheel"));

			type = new OptionGrid(options, "Object Type", position, width);
			type->setSelectionChangedCallback(MakeDelegate(this, &ObjectMenu::type_SelectionChanged));
			addMenuItem(*type);

			subMenuPos = type->getPosition();
			subMenuPos.translateY(type->getDimensions().getY());
		}

		// child menus
		circleMenu			= new SimpleObjectMenu((SimpleObject *)new Circle(), subMenuPos, width, mode);
		particleEmitterMenu	= new ParticleEmitterMenu(new ParticleEmitter(), subMenuPos, width, mode);
		squareMenu			= new SimpleObjectMenu((SimpleObject *)new Square(), subMenuPos, width, mode);
		triangleMenu		= new SimpleObjectMenu((SimpleObject *)new Triangle(), subMenuPos, width, mode);
		bombMenu			= new BombMenu(new Bomb(), subMenuPos, width, mode);
		wheelMenu			= new WheelMenu(new Wheel(), subMenuPos, width, mode);

		circleMenu->setErasedCallback(MakeDelegate(this, &ObjectMenu::object_Erased));
		particleEmitterMenu->setErasedCallback(MakeDelegate(this, &ObjectMenu::object_Erased));
		squareMenu->setErasedCallback(MakeDelegate(this, &ObjectMenu::object_Erased));
		triangleMenu->setErasedCallback(MakeDelegate(this, &ObjectMenu::object_Erased));
		bombMenu->setErasedCallback(MakeDelegate(this, &ObjectMenu::object_Erased));
	}

	void ObjectMenu::render(void)
	{
		Menu::render();

		switch(state)
		{
			case PhysicsObject::CIRCLE:
				assert(circleMenu);
				circleMenu->render();
				break;

			case PhysicsObject::SQUARE:
				assert(squareMenu);
				squareMenu->render();
				break;

			case PhysicsObject::TRIANGLE:
				assert(triangleMenu);
				triangleMenu->render();
				break;

			case PhysicsObject::PARTICLES:
				assert(particleEmitterMenu);
				particleEmitterMenu->render();
				break;

			case PhysicsObject::BOMB:
				assert(bombMenu);
				bombMenu->render();
				break;

			case PhysicsObject::WHEEL:
				assert(wheelMenu);
				wheelMenu->render();
				break;
		}
	}

	void ObjectMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void ObjectMenu::setObject(PhysicsObject *object)
	{
		state = object->getObjectType();
		setValues();

		switch(state)
		{
			case PhysicsObject::CIRCLE:
				assert(circleMenu);
				circleMenu->setObject((SimpleObject *)object);
				break;

			case PhysicsObject::SQUARE:
				assert(squareMenu);
				squareMenu->setObject((SimpleObject *)object);
				break;

			case PhysicsObject::TRIANGLE:
				assert(triangleMenu);
				triangleMenu->setObject((SimpleObject *)object);
				break;

			case PhysicsObject::PARTICLES:
				assert(particleEmitterMenu);
				particleEmitterMenu->setObject((ParticleEmitter *)object);
				break;

			case PhysicsObject::BOMB:
				assert(bombMenu);
				bombMenu->setObject((Bomb *)object);
				break;

			case PhysicsObject::WHEEL:
				assert(wheelMenu);
				wheelMenu->setObject((Wheel *)object);
				break;

			default:
				assert(false);
				break;
		}
	}

	void ObjectMenu::setValues(void)
	{
		if(mode == CREATE)
		{
			type->setSelectedItem(state);
		}

		updateState();
	}

	/* Private Member Functions */
	void ObjectMenu::object_Erased(Menu *sender, PhysicsObject *obj)
	{
		if(erased != NULL)
		{
			erased(this, obj);
		}
	}

	void ObjectMenu::type_SelectionChanged(const OptionGrid::Option &option)
	{
		if(mode == CREATE)
		{
			state = (PhysicsObject::PhysicsObjectType)option.id;
			updateState();
		}
		else
		{
			type->setSelectedItem(state);
		}
	}

	void ObjectMenu::updateState(void)
	{
		unregisterEventHandler(circleMenu);
		unregisterEventHandler(squareMenu);
		unregisterEventHandler(triangleMenu);
		unregisterEventHandler(particleEmitterMenu);
		unregisterEventHandler(bombMenu);
		unregisterEventHandler(wheelMenu);

		switch(state)
		{
			case PhysicsObject::CIRCLE:
				registerEventHandler(circleMenu);
				break;

			case PhysicsObject::SQUARE:
				registerEventHandler(squareMenu);
				break;

			case PhysicsObject::TRIANGLE:
				registerEventHandler(triangleMenu);
				break;

			case PhysicsObject::PARTICLES:
				registerEventHandler(particleEmitterMenu);
				break;

			case PhysicsObject::BOMB:
				registerEventHandler(bombMenu);
				break;

			case PhysicsObject::WHEEL:
				registerEventHandler(wheelMenu);
				break;
		}
	}
}

