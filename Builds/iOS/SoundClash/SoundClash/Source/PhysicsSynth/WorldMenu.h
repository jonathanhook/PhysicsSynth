/**
 * Class:	WorldMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class Button;
	class ColourPicker;
	class ObjectPicker;
	class Slider;
	class SoundConfig;
	class TargetButton;
	class World;

	class WorldMenu :
		public Menu
	{
	public:
		typedef FastDelegate0<> ErasedCallback;

		WorldMenu(const Point2i &position, unsigned int width, MenuMode mode);
		~WorldMenu(void);

		World			*createWorld		(void);
		virtual	void	initMenuItems		(void);
		void			setErasedCallback	(ErasedCallback erased);
		virtual void	setValues			(void);
		void			setWorld			(World *world);

	private:
		static const std::string CIRCLE_WORLD_LABEL;
		static const std::string SQUARE_WORLD_LABEL;

		Button			*erase;
		ErasedCallback	erased;
		TargetButton	*gravity;
		Slider			*size;
		ObjectPicker	*objects;
		OptionGrid		*type;
		World			*world;

		World	*cloneWorld				(World::WorldType cloneType);
		void	erase_Clicked			(UIElement *sender);
		void	gravity_TargetChanged	(const Vector2f &targetPosition);
		void	objects_ObjectSelected	(ObjectPicker *sender, PhysicsObject *obj);
		void	size_ValueChanged		(float size);
		void	type_SelectionChanged	(const OptionGrid::Option &selection);
	};
}

