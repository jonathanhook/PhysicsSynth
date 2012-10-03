/**
 * Class:	ParticleEmitterMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include "Button.h"
#include "CheckBox.h"
#include "ColourPicker.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterMenu.h"
#include "PatternPicker.h"
#include "Slider.h"
#include "Sounds.h"
#include "Synchronizer.h"
#include "TargetButton.h"

namespace PhysicsSynth
{
	/* Constructors */
	ParticleEmitterMenu::ParticleEmitterMenu(ParticleEmitter *emitter, const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, BOTTOM | LEFT | RIGHT, mode)
	{
		this->emitter = emitter;

		erased = NULL;

		initMenuItems();
		setValues();
	}

	ParticleEmitterMenu::~ParticleEmitterMenu(void)
	{
		NDELETE(emitter); // TODO: delete or not to delete?
	}

	/* Public Member Functions */
	PhysicsObject *ParticleEmitterMenu::createObject(void) const
	{
		assert(emitter);
		
		const Vector2f		&oldImpulse		= emitter->getImpulse();
		float				oldLifespan		= emitter->getLifespan();
		float				oldRate			= emitter->getRate();
		unsigned int		oldPattern		= emitter->getPattern();
		float				oldSize			= emitter->getSize();
		SoundConfig			*oldSound		= emitter->getSound();
		float				oldFriction		= emitter->getFriction();
		float				oldRestitution	= emitter->getRestitution();

		return new ParticleEmitter(oldImpulse, oldLifespan, oldRate, oldPattern, oldSize, oldSound, oldFriction, oldRestitution);
	}

	void ParticleEmitterMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		sound = new ColourPicker(Sounds::getSounds(), "Sound", position, width);
		sound->setSelectionChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::sound_SelectedItemChanged));
		addMenuItem(*sound);

		friction = new Slider("Friction", position, width);
		friction->setValueChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::friction_ValueChanged));
		addMenuItem(*friction);

		restitution = new Slider("Bounce", position, width);
		restitution->setValueChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::restitution_ValueChanged));
		addMenuItem(*restitution);

		size = new Slider("Size", position, width);
		size->setValueChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::size_ValueChanged));
		addMenuItem(*size);

		lifespan = new Slider("Lifespan", position, width);
		lifespan->setValueChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::lifespan_ValueChanged));
		addMenuItem(*lifespan);

		rate = new Slider("Rate", position, width);
		rate->setValueChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::rate_ValueChanged));
		addMenuItem(*rate);

		pattern = new PatternPicker(ParticleEmitter::PATTERN_LENGTH, "Pattern", position, width);
		pattern->setPatternChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::pattern_PatternChanged));
		addMenuItem(*pattern);

		impulse = new TargetButton("Impulse", position, width / 2);
		impulse->setTargetChangedCallback(MakeDelegate(this, &ParticleEmitterMenu::impulse_TargetChanged));
		addMenuItem(*impulse);

		sync = new Button("Sync", position, width / 2);
		sync->setClickedCallback(MakeDelegate(this, &ParticleEmitterMenu::sync_Clicked));
		addMenuItem(*sync);

		if(mode == INSPECT)
		{
			erase = new Button("Erase", position, width / 2);
			erase->setClickedCallback(MakeDelegate(this, &ParticleEmitterMenu::erase_Clicked));
			addMenuItem(*erase);

			// HACK: manuall position last button
			Point2i sp = sync->getPosition();
			sp.setY(sp.getY() + getLabelHeight() * 2);
			erase->setPosition(sp);

			dimensions.setY(dimensions.getY() - (getLabelHeight() * 2));
		}
	}

	void ParticleEmitterMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void ParticleEmitterMenu::setObject(ParticleEmitter *emitter)
	{
		this->emitter = emitter;
		setValues();
	}

	void ParticleEmitterMenu::setValues(void)
	{
		assert(emitter);

		friction->setValue(emitter->getFriction());
		restitution->setValue(emitter->getRestitution());
		size->setValue(emitter->getSize());
		lifespan->setValue(emitter->getLifespan());
		rate->setValue(emitter->getRate());
		pattern->setPattern(emitter->getPattern());
		sound->setSelectedItem(emitter->getSound());
		impulse->setTargetPosition(emitter->getImpulse());
	}

	/* Private Member Functions */
	void ParticleEmitterMenu::erase_Clicked(UIElement *sender)
	{
		if(erased != NULL)
		{
			erased(this, emitter);
		}

		assert(emitter);
		emitter->setIsMarkedForDelete(true);
		emitter = NULL;
	}

	void ParticleEmitterMenu::friction_ValueChanged(float value)
	{
		assert(emitter);
		emitter->setFriction(value);
	}

	void ParticleEmitterMenu::impulse_TargetChanged(const Vector2f &target)
	{
		assert(emitter);
		emitter->setImpulse(target);
	}

	void ParticleEmitterMenu::lifespan_ValueChanged(float value)
	{
		assert(emitter);
		emitter->setLifespan(value);
	}

	void ParticleEmitterMenu::pattern_PatternChanged(unsigned int pattern)
	{
		assert(emitter);
		emitter->setPattern(pattern);
	}

	void ParticleEmitterMenu::rate_ValueChanged(float value)
	{
		assert(emitter);
		emitter->setRate(value);
	}
	
	void ParticleEmitterMenu::restitution_ValueChanged(float value)
	{
		assert(emitter);
		emitter->setRestitution(value);
	}

	void ParticleEmitterMenu::size_ValueChanged(float value)
	{
		assert(emitter);
		emitter->setSize(value);
	}

	void ParticleEmitterMenu::sound_SelectedItemChanged	(SoundConfig *sound)
	{
		assert(emitter);
		emitter->setSound(sound);
	}

	void ParticleEmitterMenu::sync_Clicked(UIElement *sender)
	{
		assert(emitter);
		emitter->sync();

		setValues();
	}
}