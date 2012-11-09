/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
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
		enum Type { WORLD, OBJECT, SOUND, OSC_CONFIG };

		static std::vector<World *>	load(std::string fname);
		static void					save(std::string fname, std::vector<World *> worlds);

	private:
		static const unsigned int READ_BUFFER_LENGTH = 4096;

		static std::string		getBombString			(Bomb *o);
        static std::string      getOscString            (OSCSender *sender);
		static std::string		getParticleEmitterString(ParticleEmitter *o);
		static std::string		getSimpleObjectString	(SimpleObject *o);
		static SoundConfig		*getSound				(unsigned int id);
		static std::string		getSoundConfigString	(SoundConfig *sc);
		static std::string		getWheelString			(Wheel *o);
		static std::string		getWorldString			(World *w);
		static Bomb				*loadBomb				(std::string s);
		static PhysicsObject	*loadObject				(std::string s, float &px, float &py);
        static void             loadOscConfig           (std::string s);
		static ParticleEmitter	*loadParticleEmitter	(std::string s);
		static SimpleObject		*loadSimpleObject		(std::string s);
		static void				loadSoundConfig			(std::string s);
		static Wheel			*loadWheel				(std::string s);
		static World			*loadWorld				(std::string s);
	};
}