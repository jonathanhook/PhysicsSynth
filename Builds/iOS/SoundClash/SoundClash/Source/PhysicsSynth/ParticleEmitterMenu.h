/**
 * Class:	ParticleEmitterMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class Button;
	class CheckBox;
	class ColourPicker;
	class ParticleEmitter;
	class PatternPicker;
	class PhysicsObject;
	class Slider;
	class TargetButton;

	class ParticleEmitterMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;
		
		ParticleEmitterMenu(ParticleEmitter *emitter, const Point2i &position, unsigned int width, MenuMode mode);
		~ParticleEmitterMenu(void);
			
		PhysicsObject	*createObject		(void) const;
		void			initMenuItems		(void);
		void			setErasedCallback	(ErasedCallback erased);
		void			setObject			(ParticleEmitter *emitter);
		void			setValues			(void);

	private:
		Slider			*density;
		Button			*erase;
		ErasedCallback	erased;
		ParticleEmitter *emitter;
		Slider			*friction;
		TargetButton	*impulse;
		Slider			*lifespan;
		PatternPicker	*pattern;
		Slider			*rate;
		Slider			*restitution;
		Slider			*size;
		ColourPicker	*sound;
		Button			*sync;

		void erase_Clicked				(UIElement *sender);
		void friction_ValueChanged		(float value);
		void impulse_TargetChanged		(const Vector2f &target);
		void lifespan_ValueChanged		(float value);
		void pattern_PatternChanged		(unsigned int pattern);
		void rate_ValueChanged			(float value);
		void restitution_ValueChanged	(float value);
		void size_ValueChanged			(float value);
		void sound_SelectedItemChanged	(SoundConfig *sound);
		void sync_Clicked				(UIElement *sender);
	};
}

