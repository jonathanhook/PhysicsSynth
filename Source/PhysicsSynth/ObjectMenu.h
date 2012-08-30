/**
 * Class:	ObjectMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Vector2f.h>
#include "Menu.h"
#include "OptionGrid.h"
#include "PhysicsObject.h"

namespace PhysicsSynth
{
	class BombMenu;
	class ParticleEmitterMenu;
	class SimpleObjectMenu;
	class WheelMenu;

	class ObjectMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<ObjectMenu *, PhysicsObject *> ErasedCallback;

		ObjectMenu(const Point2i &position, unsigned int width, MenuMode mode);
		~ObjectMenu(void);

		PhysicsObject	*createObject				(void) const;
		void			initMenuItems				(void);
		void			render						(void);
		void			setErasedCallback			(ErasedCallback erased);
		void			setObject					(PhysicsObject *object);
		void			setValues					(void);

	private:
		static const PhysicsObject::PhysicsObjectType DEFAULT_STATE;

		BombMenu							*bombMenu;
		SimpleObjectMenu					*circleMenu;
		ErasedCallback						erased;
		ParticleEmitterMenu					*particleEmitterMenu;
		SimpleObjectMenu					*squareMenu;
		PhysicsObject::PhysicsObjectType	state;
		SimpleObjectMenu					*triangleMenu;
		OptionGrid							*type;
		WheelMenu							*wheelMenu;
		
		void object_Erased			(Menu *sender, PhysicsObject *obj);
		void type_SelectionChanged	(const OptionGrid::Option &option);
		void updateState			(void);
	};
}
