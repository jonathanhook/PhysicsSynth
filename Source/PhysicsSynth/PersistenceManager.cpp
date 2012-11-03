/**
 * Class:	PersistenceManager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <sstream>
#include "Bomb.h"
#include "Circle.h"
#include "CircularWorld.h"
#include "Manager.h"
#include "ParticleEmitter.h"
#include "PersistenceManager.h"
#include "SimpleObject.h"
#include "Sounds.h"
#include "SoundConfig.h"
#include "Square.h"
#include "SquareWorld.h"
#include "Triangle.h"
#include "Wheel.h"
#include "World.h"

namespace PhysicsSynth
{
	/* Public Static Functions */
	std::vector<World *> PersistenceManager::load(std::string fname)
	{
		std::vector<World *> worlds;
		World *cw = NULL;

		FILE *pFile = fopen(fname.c_str(), "r");
		if(pFile != NULL)
		{
			char sBuffer[READ_BUFFER_LENGTH];
			fgets(sBuffer, READ_BUFFER_LENGTH, pFile);

			while (!feof(pFile))
			{
				std::stringstream ss(sBuffer);
				
				unsigned int entryType;
				ss >> entryType;

				switch(entryType)
				{
					case SOUND:
						loadSoundConfig(ss.str());
						break;
					case WORLD:
						cw = loadWorld(ss.str());
						worlds.push_back(cw);
						break;
					case OBJECT:
						float px = 0.0f;
						float py = 0.0f;

						PhysicsObject *p = loadObject(ss.str(), px, py);
						assert(p);
						assert(cw);
						
						cw->addObject(p, Point2f(px, py));
						break;
				}

				fgets(sBuffer, READ_BUFFER_LENGTH, pFile);
			}
	
			fclose(pFile);

		}

		return worlds;
	}

	void PersistenceManager::save(std::string fname, std::vector<World *> worlds)
	{
		std::stringstream ss;

		std::vector<World *>::iterator it;
		for(it = worlds.begin(); it != worlds.end(); it++)
		{
			World *w = (*it);
			assert(w);

			// add world header
			ss << getWorldString(w);

			// add objects
			std::vector<PhysicsObject *> objects = w->getObjects();
			std::vector<PhysicsObject *>::iterator jt;
			for(jt = objects.begin(); jt != objects.end(); jt++)
			{
				PhysicsObject *o = (*jt);
				assert(o);

				switch(o->getObjectType())
				{
					case PhysicsObject::CIRCLE:
					case PhysicsObject::SQUARE:
					case PhysicsObject::TRIANGLE:
						ss << getSimpleObjectString((SimpleObject *)o);
						break;
					case PhysicsObject::PARTICLES:
						ss << getParticleEmitterString((ParticleEmitter *)o);
						break;
					case PhysicsObject::BOMB:
						ss << getBombString((Bomb *)o);
						break;
					case PhysicsObject::WHEEL:
						ss << getWheelString((Wheel *)o);
						break;
				}
			}
		}

		std::vector<SoundConfig *> sounds = Sounds::getSounds();
		for(unsigned int i = 0; i < sounds.size(); i++)
		{
			SoundConfig *sc = sounds[i];
			assert(sc);

			ss << getSoundConfigString(sc);
		}

		FILE *pFile = fopen(fname.c_str(), "w");
		if(pFile != NULL)
		{
			std::string out = ss.str();
			fputs(out.c_str(), pFile);
			fclose(pFile);
		}
	}

	/* Private Static Functions */
	std::string PersistenceManager::getBombString(Bomb *o)
	{
		assert(o);

		std::stringstream ss;
		ss	<< OBJECT					<< ','
		<< o->getObjectType()			<< ','
		<< o->getPosition().getX()		<< ','
		<< o->getPosition().getY()		<< ','
		<< o->getSound()->getSampleId() << ','
		<< o->getSize()					<< ','
		<< o->getRate()					<< ','
		<< o->getIntensity()			<< ','
		<< o->getPattern()				<< endl;

		return ss.str();
	}

	std::string PersistenceManager::getParticleEmitterString(ParticleEmitter *o)
	{
		assert(o);

		std::stringstream ss;
		ss	<< OBJECT					<< ','
		<< o->getObjectType()			<< ','
		<< o->getPosition().getX()		<< ','
		<< o->getPosition().getY()		<< ','
		<< o->getSound()->getSampleId() << ','
		<< o->getFriction()				<< ','
		<< o->getRestitution()			<< ','
		<< o->getSize()					<< ','
		<< o->getLifespan()				<< ','
		<< o->getRate()					<< ','
		<< o->getPattern()				<< ','
		<< o->getImpulse().getX()		<< ','
		<< o->getImpulse().getY()		<< endl;

		return ss.str();
	}

	std::string PersistenceManager::getSimpleObjectString(SimpleObject *o)
	{
		assert(o);

		std::stringstream ss;
		ss	<< OBJECT						<< ','
			<< o->getObjectType()			<< ','
			<< o->getPosition().getX()		<< ','
			<< o->getPosition().getY()		<< ','
			<< o->getSound()->getSampleId() << ','
			<< o->getFriction()				<< ','
			<< o->getRestitution()			<< ','
			<< o->getSize()					<< ','
			<< o->getIsLocked()				<< std::endl;

		return ss.str();
	}

	SoundConfig *PersistenceManager::getSound(unsigned int id)
	{
		std::vector<SoundConfig *> sounds = Sounds::getSounds();
		for(unsigned int i = 0; i < sounds.size(); i++)
		{
			SoundConfig *s = sounds[i];
			assert(s);

			if(s->getSampleId() == id)
			{
				return s;
			}
		}

		return &Sounds::NO_SOUND;
	}

	std::string	PersistenceManager::getSoundConfigString(SoundConfig *sc)
	{
		assert(sc);

		std::stringstream ss;
		ss	<< SOUND << ','
            << sc->getSampleId();

		std::map<unsigned int, SoundConfig::PhysicalProperty> mappings = sc->getImpulseMappings();
		for(unsigned int i = 0; i < 7; i++)
		{
			ss << ',' << mappings[i];
		}

		ss << std::endl;
		return ss.str();
	}

	std::string PersistenceManager::getWheelString(Wheel *o)
	{
		assert(o);

		std::stringstream ss;
		ss	<< OBJECT						<< ','
			<< o->getObjectType()			<< ','
			<< o->getPosition().getX()		<< ','
			<< o->getPosition().getY()		<< ','
			<< o->getSound()->getSampleId() << ','
			<< o->getSize()					<< ','
			<< o->getRate()					<< ','
			<< o->getPattern()				<< endl;

		return ss.str();
	}

	std::string PersistenceManager::getWorldString(World *w)
	{
		assert(w);

		std::stringstream ss;
		ss	<< WORLD					<< ','
			<< w->getWorldType()		<< ','
			<< w->getTrack()			<< ','
			<< w->getPosition().getX()	<< ','
			<< w->getPosition().getY()	<< ','
			<< w->getSize()				<< ','
			<< w->getGravity().getX()	<< ','
			<< w->getGravity().getY()	<< std::endl;

		return ss.str();
	}

	Bomb *PersistenceManager::loadBomb(std::string s)
	{
		unsigned int	type		= 0;
		unsigned int	oType		= 0;
		float			x			= 0.0f;
		float			y			= 0.0f;
		unsigned int	sampleId	= 0;
		float			size		= 0.0f;
		float			rate		= 0.0f;
		float			intensity	= 0.0f;
		unsigned int	pattern		= 0;
			
		sscanf(s.c_str(), "%d,%d,%f,%f,%d,%f,%f,%f,%d", &type, &oType, &x, &y, &sampleId, &size, &rate, &intensity, &pattern);

		return new Bomb(intensity, rate, pattern, size, getSound(sampleId));
	}

	PhysicsObject *PersistenceManager::loadObject(std::string s, float &px, float &py)
	{
		unsigned int	type	= 0;	
		unsigned int	wType	= 0;

		sscanf(s.c_str(), "%d,%d,%f,%f", &type, &wType, &px, &py);

		switch(wType)
		{
			case PhysicsObject::CIRCLE:
			case PhysicsObject::SQUARE:
			case PhysicsObject::TRIANGLE:
				return loadSimpleObject(s);
			case PhysicsObject::PARTICLES:
				return loadParticleEmitter(s);
			case PhysicsObject::BOMB:
				return loadBomb(s);
			case PhysicsObject::WHEEL:
				return loadWheel(s);
		}

		return NULL;
	}

	ParticleEmitter *PersistenceManager::loadParticleEmitter(std::string s)
	{
		unsigned int	type		= 0;
		unsigned int	oType		= 0;
		float			x			= 0.0f;
		float			y			= 0.0f;
		unsigned int	sampleId	= 0;
		float			friction	= 0.0f;
		float			restitution	= 0.0f;
		float			size		= 0.0f;
		float			lifespan	= 0.0f;
		float			rate		= 0.0f;
		unsigned int	pattern		= 0;
		float			impulseX	= 0.0f;
		float			impulseY	= 0.0f;

		sscanf(s.c_str(), "%d,%d,%f,%f,%d,%f,%f,%f,%f,%f,%d,%f,%f", &type, &oType, &x, &y, &sampleId, &friction, &restitution, &size, &lifespan, &rate, &pattern, &impulseX, &impulseY);

		return new ParticleEmitter(Vector2f(impulseX, impulseY), lifespan, rate, pattern, size, getSound(sampleId), friction, restitution); 
	}

	SimpleObject *PersistenceManager::loadSimpleObject(std::string s)
	{
		unsigned int	type		= 0;
		unsigned int	oType		= 0;
		float			x			= 0.0f;
		float			y			= 0.0f;
		unsigned int	sampleId	= 0;
		float			friction	= 0.0f;
		float			restitution	= 0.0f;
		float			size		= 0.0f;
		unsigned int	isLocked	= 0;
			
		sscanf(s.c_str(), "%d,%d,%f,%f,%d,%f,%f,%f,%d", &type, &oType, &x, &y, &sampleId, &friction, &restitution, &size, &isLocked);

		switch(oType)
		{
			case PhysicsObject::CIRCLE:
				return new Circle(isLocked != 0, size, getSound(sampleId), friction, restitution);
			case PhysicsObject::SQUARE:
				return new Square(isLocked != 0, size, getSound(sampleId), friction, restitution);
			case PhysicsObject::TRIANGLE:
				return new Triangle(isLocked != 0, size, getSound(sampleId), friction, restitution);
		}

		return NULL;
	}

	void PersistenceManager::loadSoundConfig(std::string s)
	{
		unsigned int type	= 0;
		unsigned int id		= 0;
		unsigned int mode	= 0;
		unsigned int m0		= 0;
		unsigned int m1		= 0;
		unsigned int m2		= 0;
		unsigned int m3		= 0;
		unsigned int m4		= 0;
		unsigned int m5		= 0;
		unsigned int m6		= 0;

		sscanf(s.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &type, &id, &mode, &m0, &m1, &m2, &m3, &m4, &m5, &m6);

		std::vector<SoundConfig *> sounds	= Sounds::getSounds();
		SoundConfig *sc						= sounds[id];
		assert(sc);
		
		sc->updateMapping(0, (SoundConfig::PhysicalProperty)m0);
		sc->updateMapping(1, (SoundConfig::PhysicalProperty)m1);
		sc->updateMapping(2, (SoundConfig::PhysicalProperty)m2);
		sc->updateMapping(3, (SoundConfig::PhysicalProperty)m3);
		sc->updateMapping(4, (SoundConfig::PhysicalProperty)m4);
		sc->updateMapping(5, (SoundConfig::PhysicalProperty)m5);
		sc->updateMapping(6, (SoundConfig::PhysicalProperty)m6);
	}

	Wheel *PersistenceManager::loadWheel(std::string s)
	{
		unsigned int	type		= 0;
		unsigned int	oType		= 0;
		float			x			= 0.0f;
		float			y			= 0.0f;
		unsigned int	sampleId	= 0;
		float			size		= 0.0f;
		float			rate		= 0.0f;
		unsigned int	pattern		= 0;
			
		sscanf(s.c_str(), "%d,%d,%f,%f,%d,%f,%f,%d", &type, &oType, &x, &y, &sampleId, &size, &rate, &pattern);

		return new Wheel(rate, pattern, size, getSound(sampleId));
	}

	World *PersistenceManager::loadWorld(std::string s)
	{
		unsigned int	type	= 0;	
		unsigned int	wType	= 0;
		unsigned int	track	= 0;
		float			x		= 0.0f;
		float			y		= 0.0f;
		float			size	= 0.0f;
		float			gx		= 0.0f;
		float			gy		= 0.0f;

		sscanf(s.c_str(), "%d,%d,%d,%f,%f,%f,%f,%f", &type, &wType, &track, &x, &y, &size, &gx, &gy);
		
		Manager::setTrackId(track);

		switch(wType)
		{
			case World::CIRCULAR:
				return new CircularWorld(track, Point2f(x, y), Vector2f(gx, gy), size); 
			case World::SQUARE:
				return new SquareWorld(track, Point2f(x, y), Vector2f(gx, gy), size); 
		}

		return NULL;
	}
}

