/**
 * Class:	PersistenceManager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <string>
#include <sstream>
#include <JDHUtility/Vector2f.h>

namespace PhysicsSynth
{
	class Bomb;
	class ParticleEmitter;
	class SimpleObject;
	class SoundConfig;
	class Wheel;
	class World;

	class PersistenceManager
	{
	public:
		enum Type { WORLD, OBJECT, SOUND };

		static std::vector<World *>	load(std::string fname);
		static void					save(std::string fname, std::vector<World *> worlds);

	private:
		static const unsigned int READ_BUFFER_LENGTH = 4096;

		static std::string		getBombString			(Bomb *o);
		static std::string		getParticleEmitterString(ParticleEmitter *o);
		static std::string		getSimpleObjectString	(SimpleObject *o);
		static SoundConfig		*getSound				(unsigned int id);
		static std::string		getSoundConfigString	(SoundConfig *sc);
		static std::string		getWheelString			(Wheel *o);
		static std::string		getWorldString			(World *w);
		static Bomb				*loadBomb				(std::string s);
		static PhysicsObject	*loadObject				(std::string s, float &px, float &py);
		static ParticleEmitter	*loadParticleEmitter	(std::string s);
		static SimpleObject		*loadSimpleObject		(std::string s);
		static void				loadSoundConfig			(std::string s);
		static Wheel			*loadWheel				(std::string s);
		static World			*loadWorld				(std::string s);
	};
}